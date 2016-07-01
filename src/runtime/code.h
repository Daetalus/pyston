// Copyright (c) 2014-2016 Dropbox, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PYSTON_RUNTIME_CODE_H
#define PYSTON_RUNTIME_CODE_H

#include "Python.h"

#include "runtime/types.h"

namespace pyston {

class BoxedCode : public Box {
public:
    FunctionMetadata* f;
    Box* _filename;
    Box* _name;
    int _firstline;

    BoxedCode(FunctionMetadata* f) : f(f), _filename(NULL), _name(NULL), _firstline(-1) {}
    BoxedCode(Box* filename, Box* name, int firstline)
        : f(NULL), _filename(filename), _name(name), _firstline(firstline) {
        Py_XINCREF(filename);
        Py_XINCREF(name);
    }

    DEFAULT_CLASS(code_cls);

    int co_nlocals;		/* #local variables */
    int co_stacksize;		/* #entries needed for evaluation stack */
    PyObject *co_code;		/* instruction opcodes */
    PyObject *co_consts;	/* list (constants used) */
    PyObject *co_names;		/* list of strings (names used) */
    PyObject *co_freevars;	/* tuple of strings (free variable names) */
    PyObject *co_cellvars;      /* tuple of strings (cell variable names) */
    // #<{(| The rest doesn't count for hash/cmp |)}>#
    // PyObject *co_lnotab;	#<{(| string (encoding addr<->lineno mapping) See
	// 			   Objects/lnotab_notes.txt for details. |)}>#
    // void *co_zombieframe;     #<{(| for optimization only (see frameobject.c) |)}>#
    // PyObject *co_weakreflist;   #<{(| to support weakrefs to code objects |)}>#
    // These need to be static functions rather than methods because function
    // pointers could point to them.
    static BORROWED(Box*) name(Box* b, void*) noexcept;
    static BORROWED(Box*) filename(Box* b, void*) noexcept;
    static Box* co_name(Box* b, void*) noexcept;
    static Box* co_filename(Box* b, void*) noexcept;
    static Box* firstlineno(Box* b, void*) noexcept;
    static Box* argcount(Box* b, void*) noexcept;
    static Box* varnames(Box* b, void*) noexcept;
    static Box* flags(Box* b, void*) noexcept;

    static int traverse(Box* self, visitproc visit, void* arg) noexcept;
    static void dealloc(Box* b) noexcept;
};
}

#endif
