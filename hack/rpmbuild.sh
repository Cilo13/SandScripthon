#!/bin/bash
# Copyright 2016 Sandvine Incorporated ULC. All rights reserved.

# This script is capable of setting up a temporary directory
# skeleton for rpmbuild to be happy. It will make a tarball
# of the project's source code and place under the right
# directory and tell rpmbuild to execute your rpm/spec file.

# Use `rpm -qip` or `rpm -qlp` afterwards for details about your rpm.

set -ex

VERSION=${VERSION:-tip}
ROOT=/tmp/rpmbuild.$$
trap "rm -rf ${ROOT}" EXIT

function fromspec() {
	echo -ne $(grep -m1 $2 $1 | cut -d: -f2 | tr -d ' ')
}

function setversion() {
	sed -i.orig "s/^Version: .*/Version: ${VERSION}/g" $1
	PKGNAME=`fromspec $1 ^Name:`-${VERSION}
}

# makerpm builds the rpm package and saves it in the current directory.
function makerpm() {
	topdir=${ROOT}/top
	mkdir -p ${topdir}/BUILD ${topdir}/RPMS ${topdir}/SRPMS ${topdir}/SOURCES ${topdir}/SPECS
	cp $1/rpm/spec ${topdir}/SPECS
	setversion ${topdir}/SPECS/spec
	tar czf ${topdir}/SOURCES/${PKGNAME}.tar.gz $1
	buildroot=${ROOT}/root/
	mkdir -p $buildroot || true
	export DESTDIR=${buildroot}
	rpmbuild \
		--target x86_64-redhat-linux \
		--define "_topdir ${topdir}" \
		--buildroot ${buildroot} \
		-bb ${topdir}/SPECS/spec

	if [ ! -z "$1" ]; then
		mv ${topdir}/RPMS/x86_64/* $1
	else
		mv ${topdir}/RPMS/x86_64/* .
	fi
}

if [ -z "$1" ]
then
	echo $0 '<project-dir>'
	echo The project directory must contain an rpm/spec file.
	exit 1
fi

makerpm $1
