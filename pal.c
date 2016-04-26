/* SandScript meets Python.
 *
 * This is a SandScript shared library that loads a Python interpreter
 * and let users write policy subsystems in Python. It depends on the
 * special "SandScript" Python module to do so.
 *
 * At this point, the code is pretty alpha and may have bugs and
 * memory leaks.
 *
 * Due to a limitation of the shared library API, we can only export
 * so many functions, currently set to max=100.
*/

#include <Python.h>
#include <syslog.h>

#include "pal.h"

#ifndef VERSION
#define VERSION "tip"
#endif

#ifndef GITCOMMIT
#define GITCOMMIT "HEAD"
#endif

#define PYMOD     "SandScript"
#define PYUSERMOD "policy"
#define PYUSERDIR "/usr/local/sandvine/etc"

PyObject* pyFuncList[100]; // Max functions that can exist.

bool pslFunc(PyObject* item, psl_Value* resp, const psl_Value* const* args) {
	PyObject* fp = PyTuple_GetItem(item, 0);
	PyObject* al = PyTuple_GetItem(item, 2);
	PyObject* rt = PyTuple_GetItem(item, 3);

	int i, na = PyTuple_Size(al);
	PyObject* pa = PyTuple_New(na);

	for (i=0; i < na; i++) {
		PyObject* arg = NULL;
		switch (PyInt_AsLong(PyTuple_GetItem(al, i))) {
		case psl_boolean:
			arg = args[i]->b ? Py_True : Py_False;
			break;
		case psl_string:
			arg = PyString_FromStringAndSize(
				args[i]->s.begin,
				args[i]->s.length
			);
			break;
		case psl_integer:
			arg = PyInt_FromLong((long) args[i]->i);
			break;
		case psl_float:
			arg = PyFloat_FromDouble(args[i]->f);
			break;
		case psl_ipaddress:
			arg = PyByteArray_FromStringAndSize(
				(const char*) args[i]->a,
				sizeof(args[i]->a)
			);
			break;
		}

		if (arg) {
			Py_INCREF(arg);
			PyTuple_SetItem(pa, i, arg);
		}
	}

	PyObject* pr = PyObject_CallObject(fp, pa);

	for (i=0; i < PyTuple_Size(pa); i++) {
		Py_DECREF(PyTuple_GetItem(pa, i));
	}
	Py_DECREF(pa);

	if (!pr) return false;
	if (pr == Py_None) {
		Py_DECREF(pr);
		return false;
	}

	bool rv = false;

	switch (PyInt_AsLong(rt)) {
	case psl_boolean:
		if (PyBool_Check(pr)) {
			resp->b = pr == Py_True;
			rv = true;
		}
		break;
	case psl_string:
		if (PyString_Check(pr)) {
			resp->s.begin = PyString_AsString(pr);
			resp->s.length = strlen(resp->s.begin);
			rv = true;
		}
		break;
	case psl_integer:
		if (PyInt_Check(pr)) {
			resp->i = PyInt_AsLong(pr);
			rv = true;
		}
		break;
	case psl_float:
		if (PyFloat_Check(pr)) {
			resp->f = PyFloat_AsDouble(pr);
			rv = true;
		}
		break;
	case psl_ipaddress:
		if (PyByteArray_Check(pr)) {
			char* s = PyByteArray_AsString(pr);
			int sl = PyByteArray_Size(pr);
			if (sl <= 16) {
				memcpy(resp->a, s, sl);
				rv = true;
			}
		}
		break;
	}

	Py_DECREF(pr);
	return rv;
}

bool pslFunc0(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[0], resp, args);
}

bool pslFunc1(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[1], resp, args);
}

bool pslFunc2(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[2], resp, args);
}

bool pslFunc3(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[3], resp, args);
}

bool pslFunc4(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[4], resp, args);
}

bool pslFunc5(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[5], resp, args);
}

bool pslFunc6(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[6], resp, args);
}

bool pslFunc7(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[7], resp, args);
}

bool pslFunc8(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[8], resp, args);
}

bool pslFunc9(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[9], resp, args);
}

bool pslFunc10(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[10], resp, args);
}

bool pslFunc11(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[11], resp, args);
}

bool pslFunc12(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[12], resp, args);
}

bool pslFunc13(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[13], resp, args);
}

bool pslFunc14(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[14], resp, args);
}

bool pslFunc15(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[15], resp, args);
}

bool pslFunc16(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[16], resp, args);
}

bool pslFunc17(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[17], resp, args);
}

bool pslFunc18(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[18], resp, args);
}

bool pslFunc19(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[19], resp, args);
}

bool pslFunc20(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[20], resp, args);
}

bool pslFunc21(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[21], resp, args);
}

bool pslFunc22(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[22], resp, args);
}

bool pslFunc23(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[23], resp, args);
}

bool pslFunc24(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[24], resp, args);
}

bool pslFunc25(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[25], resp, args);
}

bool pslFunc26(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[26], resp, args);
}

bool pslFunc27(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[27], resp, args);
}

bool pslFunc28(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[28], resp, args);
}

bool pslFunc29(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[29], resp, args);
}

bool pslFunc30(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[30], resp, args);
}

bool pslFunc31(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[31], resp, args);
}

bool pslFunc32(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[32], resp, args);
}

bool pslFunc33(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[33], resp, args);
}

bool pslFunc34(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[34], resp, args);
}

bool pslFunc35(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[35], resp, args);
}

bool pslFunc36(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[36], resp, args);
}

bool pslFunc37(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[37], resp, args);
}

bool pslFunc38(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[38], resp, args);
}

bool pslFunc39(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[39], resp, args);
}

bool pslFunc40(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[40], resp, args);
}

bool pslFunc41(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[41], resp, args);
}

bool pslFunc42(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[42], resp, args);
}

bool pslFunc43(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[43], resp, args);
}

bool pslFunc44(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[44], resp, args);
}

bool pslFunc45(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[45], resp, args);
}

bool pslFunc46(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[46], resp, args);
}

bool pslFunc47(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[47], resp, args);
}

bool pslFunc48(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[48], resp, args);
}

bool pslFunc49(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[49], resp, args);
}

bool pslFunc50(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[50], resp, args);
}

bool pslFunc51(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[51], resp, args);
}

bool pslFunc52(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[52], resp, args);
}

bool pslFunc53(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[53], resp, args);
}

bool pslFunc54(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[54], resp, args);
}

bool pslFunc55(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[55], resp, args);
}

bool pslFunc56(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[56], resp, args);
}

bool pslFunc57(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[57], resp, args);
}

bool pslFunc58(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[58], resp, args);
}

bool pslFunc59(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[59], resp, args);
}

bool pslFunc60(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[60], resp, args);
}

bool pslFunc61(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[61], resp, args);
}

bool pslFunc62(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[62], resp, args);
}

bool pslFunc63(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[63], resp, args);
}

bool pslFunc64(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[64], resp, args);
}

bool pslFunc65(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[65], resp, args);
}

bool pslFunc66(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[66], resp, args);
}

bool pslFunc67(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[67], resp, args);
}

bool pslFunc68(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[68], resp, args);
}

bool pslFunc69(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[69], resp, args);
}

bool pslFunc70(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[70], resp, args);
}

bool pslFunc71(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[71], resp, args);
}

bool pslFunc72(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[72], resp, args);
}

bool pslFunc73(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[73], resp, args);
}

bool pslFunc74(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[74], resp, args);
}

bool pslFunc75(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[75], resp, args);
}

bool pslFunc76(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[76], resp, args);
}

bool pslFunc77(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[77], resp, args);
}

bool pslFunc78(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[78], resp, args);
}

bool pslFunc79(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[79], resp, args);
}

bool pslFunc80(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[80], resp, args);
}

bool pslFunc81(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[81], resp, args);
}

bool pslFunc82(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[82], resp, args);
}

bool pslFunc83(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[83], resp, args);
}

bool pslFunc84(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[84], resp, args);
}

bool pslFunc85(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[85], resp, args);
}

bool pslFunc86(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[86], resp, args);
}

bool pslFunc87(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[87], resp, args);
}

bool pslFunc88(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[88], resp, args);
}

bool pslFunc89(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[89], resp, args);
}

bool pslFunc90(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[90], resp, args);
}

bool pslFunc91(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[91], resp, args);
}

bool pslFunc92(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[92], resp, args);
}

bool pslFunc93(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[93], resp, args);
}

bool pslFunc94(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[94], resp, args);
}

bool pslFunc95(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[95], resp, args);
}

bool pslFunc96(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[96], resp, args);
}

bool pslFunc97(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[97], resp, args);
}

bool pslFunc98(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[98], resp, args);
}

bool pslFunc99(psl_Value* resp, const psl_Value* const* args) {
	return pslFunc(pyFuncList[99], resp, args);
}

psl_Function* pslFuncList [] = {
	&pslFunc0,
	&pslFunc1,
	&pslFunc2,
	&pslFunc3,
	&pslFunc4,
	&pslFunc5,
	&pslFunc6,
	&pslFunc7,
	&pslFunc8,
	&pslFunc9,
	&pslFunc10,
	&pslFunc11,
	&pslFunc12,
	&pslFunc13,
	&pslFunc14,
	&pslFunc15,
	&pslFunc16,
	&pslFunc17,
	&pslFunc18,
	&pslFunc19,
	&pslFunc20,
	&pslFunc21,
	&pslFunc22,
	&pslFunc23,
	&pslFunc24,
	&pslFunc25,
	&pslFunc26,
	&pslFunc27,
	&pslFunc28,
	&pslFunc29,
	&pslFunc30,
	&pslFunc31,
	&pslFunc32,
	&pslFunc33,
	&pslFunc34,
	&pslFunc35,
	&pslFunc36,
	&pslFunc37,
	&pslFunc38,
	&pslFunc39,
	&pslFunc40,
	&pslFunc41,
	&pslFunc42,
	&pslFunc43,
	&pslFunc44,
	&pslFunc45,
	&pslFunc46,
	&pslFunc47,
	&pslFunc48,
	&pslFunc49,
	&pslFunc50,
	&pslFunc51,
	&pslFunc52,
	&pslFunc53,
	&pslFunc54,
	&pslFunc55,
	&pslFunc56,
	&pslFunc57,
	&pslFunc58,
	&pslFunc59,
	&pslFunc60,
	&pslFunc61,
	&pslFunc62,
	&pslFunc63,
	&pslFunc64,
	&pslFunc65,
	&pslFunc66,
	&pslFunc67,
	&pslFunc68,
	&pslFunc69,
	&pslFunc70,
	&pslFunc71,
	&pslFunc72,
	&pslFunc73,
	&pslFunc74,
	&pslFunc75,
	&pslFunc76,
	&pslFunc77,
	&pslFunc78,
	&pslFunc79,
	&pslFunc80,
	&pslFunc81,
	&pslFunc82,
	&pslFunc83,
	&pslFunc84,
	&pslFunc85,
	&pslFunc86,
	&pslFunc87,
	&pslFunc88,
	&pslFunc89,
	&pslFunc90,
	&pslFunc91,
	&pslFunc92,
	&pslFunc93,
	&pslFunc94,
	&pslFunc95,
	&pslFunc96,
	&pslFunc97,
	&pslFunc98,
	&pslFunc99,
};

psl_DataType* buildFuncArgs(PyObject* args) {
	int na = PyTuple_Size(args);
	psl_DataType* pa = calloc(na, sizeof(psl_DataType));
	assert(pa);

	int i;
	for (i=0; i < na; i++) {
		PyObject* arg = PyTuple_GetItem(args, i);
		if (!PyInt_Check(arg)) return NULL;
		Py_INCREF(arg);
		pa[i] = PyInt_AsLong(arg);
		//Py_DECREF(arg);
	}
	return pa;
}

psl_Manifest* buildManifest(PyObject* fl) {
	int nf = PyList_Size(fl);
	int max = sizeof(pslFuncList) / sizeof(pslFuncList[0]);
	if (nf < 1 || nf > max) return NULL;

	psl_FunctionDescription** fd = calloc(nf, sizeof(psl_FunctionDescription*));
	assert(fd);

	int i;
	for (i=0; i < nf; i++) {
		PyObject* item = PyList_GetItem(fl, i);
		if (!PyTuple_Check(item) && PyTuple_Size(item) != 4)
			return NULL;
		Py_INCREF(item);

		PyObject* func = PyTuple_GetItem(item, 0);
		if (!PyCallable_Check(func)) return NULL;
		Py_INCREF(func);

		PyObject* name = PyTuple_GetItem(item, 1);
		if (!PyString_Check(name)) return NULL;
		Py_INCREF(name);

		PyObject* args = PyTuple_GetItem(item, 2);
		if (!PyTuple_Check(args)) return NULL;
		psl_DataType* pslargs = buildFuncArgs(args);
		if (!pslargs) return NULL;
		Py_INCREF(args);

		PyObject* retval = PyTuple_GetItem(item, 3);
		if (!PyInt_Check(retval)) return NULL;
		psl_DataType pslretval = PyInt_AsLong(retval);
		Py_INCREF(retval);

		fd[i] = malloc(sizeof(psl_FunctionDescription));
		assert(fd[i]);
		fd[i]->functionName = PyString_AsString(name);
		fd[i]->flags = 0;
		fd[i]->functionPointer = pslFuncList[i];
		fd[i]->returnType = pslretval;
		fd[i]->numArgs = PyTuple_Size(args);
		fd[i]->argTypes = pslargs;
		pyFuncList[i] = item;
	}

	psl_Manifest* m = malloc(sizeof(psl_Manifest));
	assert(m);

	m->version = 1;
	m->numFunctionDescriptions = nf;
	m->functionDescriptions = (const psl_FunctionDescription* const*) fd;

	return m;
}

psl_GetManifest GetManifest;
const psl_Manifest* GetManifest() {
	syslog(LOG_INFO, "SandScripthon %s (%s)", VERSION, GITCOMMIT);
	Py_Initialize();

	// Set path.
	PyObject* path = PyString_FromString(PYUSERDIR);
	PyList_Insert(PySys_GetObject("path"), 0, path);
	Py_INCREF(path);

	// Import SandScript module.
	PyObject* sf = PyImport_ImportModule(PYMOD);
	if (!sf) goto fail;
	Py_INCREF(sf);

	// Import user module.
	PyObject* uf = PyImport_ImportModule(PYUSERMOD);
	if (!uf) goto fail;
	Py_INCREF(uf);

	// Load list of registered functions.
	PyObject* fl = PyObject_GetAttrString(sf, "_func");
	if (!PyList_Check(fl)) goto fail;
	Py_INCREF(fl);

	psl_Manifest* m = buildManifest(fl);
	if (!m) goto fail;
	return m;

fail:
	if (PyErr_Occurred()) {
		PyObject *ptype = NULL, *pvalue = NULL, *ptraceback = NULL;
		PyErr_Fetch(&ptype, &pvalue, &ptraceback);
		if (pvalue)
		syslog(LOG_ERR, "SandScripthon error: %s", PyString_AsString(pvalue));
		if (ptraceback)
		syslog(LOG_ERR, "SandScripthon traceback: %s", PyString_AsString(ptraceback));
	}
	Py_Finalize();
	return NULL;
}

/*
int main() {
	const psl_Manifest* m = GetManifest();
	if (m) fprintf(stderr, "got %p\n", m);
}
*/
