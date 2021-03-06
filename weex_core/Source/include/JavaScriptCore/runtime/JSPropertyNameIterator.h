/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#pragma once

#include "JSObject.h"
#include "JSPropertyNameEnumerator.h"

namespace JSC {

class JSPropertyNameIterator : public JSNonFinalObject {
public:
    typedef JSNonFinalObject Base;

    enum class EnumerationPhase : uint32_t {
        IndexedNames,
        StructureNames,
        GenericNames,
        Done
    };

    DECLARE_EXPORT_INFO;

    static Structure* createStructure(VM& vm, JSGlobalObject* globalObject, JSValue prototype)
    {
        return Structure::create(vm, globalObject, prototype, TypeInfo(ObjectType, StructureFlags), info());
    }

    static JSPropertyNameIterator* create(ExecState*, Structure*, JSObject*);

    JSPropertyNameIterator* clone(ExecState*);
    bool next(ExecState*, JSValue&);

    JSValue iteratedValue() const { return m_iteratedObject.get(); }

    static void visitChildren(JSCell*, SlotVisitor&);

private:
    JSPropertyNameIterator(VM&, Structure*, JSObject*, JSPropertyNameEnumerator*);

    void finishCreation(VM&, JSGlobalObject*);

    static JSPropertyNameIterator* create(ExecState*, Structure*, JSObject*, JSPropertyNameEnumerator*);

    WriteBarrier<JSObject> m_iteratedObject;
    WriteBarrier<JSPropertyNameEnumerator> m_propertyNameEnumerator;
    EnumerationPhase m_enumerationPhase;
    uint32_t m_cursor;
};

} // namespace JSC
