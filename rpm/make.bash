#!/bin/bash
# Copyright 2015 Sandvine Incorporated ULC. All rights reserved.
# Use of this source code is governed by a license that can be
# found in the LICENSE file.

# This script builds an rpm package for the SDE.
# Use `rpm -qip` or `rpm -qlp` afterwards to see its contents.

#set -ex

VERSION=1.0
NAME=SandScripthon-${VERSION}

ROOT=/tmp/rpmbuild.$$
trap "rm -rf ${ROOT}" EXIT

# maketar makes a gzipped tarball with the files that will be
# in the final rpm package.
function maketar() {
	tmp=$1/tmp
	DESTDIR=$tmp/${NAME} make -C .. clean install

	pushd $tmp
	tar czf ${NAME}.tar.gz $NAME
	popd

	mv $tmp/${NAME}.tar.gz $1
	rm -rf $tmp
}

# makerpm builds the rpm package and saves it in the current directory.
function makerpm() {
	topdir=${ROOT}/top
	mkdir -p ${topdir}/RPMS ${topdir}/BUILD ${topdir}/SOURCES

	maketar ${topdir}/SOURCES

	buildroot=${ROOT}/root
	mkdir -p $buildroot || true

	rpmbuild \
		--target amd64-redhat-linux \
		--define "_topdir ${topdir}" \
		--buildroot ${buildroot} \
		-bb spec

	mv ${topdir}/RPMS/amd64/* .
}

makerpm
