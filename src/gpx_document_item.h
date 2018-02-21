/****************************************************************************
** Copyright (c) 2016, Fougue Ltd. <http://www.fougue.pro>
** All rights reserved.
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions
** are met:
**
**     1. Redistributions of source code must retain the above copyright
**        notice, this list of conditions and the following disclaimer.
**
**     2. Redistributions in binary form must reproduce the above
**        copyright notice, this list of conditions and the following
**        disclaimer in the documentation and/or other materials provided
**        with the distribution.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/

#pragma once

#include "property_builtins.h"
#include "property_enumeration.h"

#include <QtCore/QCoreApplication>
#include <AIS_InteractiveObject.hxx>
#include <Graphic3d_NameOfMaterial.hxx>

namespace Mayo {

class DocumentItem;

class GpxDocumentItem : public PropertyOwner
{
    Q_DECLARE_TR_FUNCTIONS(Mayo::GpxDocumentItem)

public:
    GpxDocumentItem();

    virtual DocumentItem* documentItem() const = 0;
    virtual Handle_AIS_InteractiveObject handleGpxObject() const = 0;
    virtual AIS_InteractiveObject* gpxObject() const = 0;

    PropertyBool propertyIsVisible;
    PropertyEnumeration propertyMaterial;
    PropertyOccColor propertyColor;

protected:
    void onPropertyChanged(Property* prop) override;

    void initForGpxBRepShape(const Handle_AIS_InteractiveObject& hndGpx);
};

template<typename DOC_ITEM, typename GPX_OBJECT, typename HND_GPX_OBJECT>
class GpxCovariantDocumentItem : public GpxDocumentItem
{
public:
    GpxCovariantDocumentItem(DOC_ITEM* item);
    GpxCovariantDocumentItem(DOC_ITEM* item, const HND_GPX_OBJECT& hndGpx);

    DOC_ITEM* documentItem() const override;
    Handle_AIS_InteractiveObject handleGpxObject() const override;
    GPX_OBJECT* gpxObject() const override;

protected:
    DOC_ITEM* m_docItem = nullptr;
    HND_GPX_OBJECT m_hndGpxObject;
};

class GpxBRepShapeCommonProperties
{
    Q_DECLARE_TR_FUNCTIONS(Mayo::GpxBRepShapeCommonProperties)

public:
    PropertyInt propertyTransparency;
    PropertyEnumeration propertyDisplayMode;
    PropertyBool propertyShowFaceBoundary;

protected:
    GpxBRepShapeCommonProperties(PropertyOwner* owner);

    void initCommonProperties(
            PropertyOwner* owner, const Handle_AIS_InteractiveObject& hndGpx);
    void handleCommonPropertyChange(
            Property* prop, const Handle_AIS_InteractiveObject& hndGpx);
    void handlePropertyMaterial(
            PropertyEnumeration* prop, const Handle_AIS_InteractiveObject& hndGpx);
    void handlePropertyColor(
            PropertyOccColor* prop, const Handle_AIS_InteractiveObject& hndGpx);

private:
    static const Enumeration& enum_DisplayMode();
};

// --
// -- Implementation
// --

template<typename DOC_ITEM, typename GPX_OBJECT, typename HND_GPX_OBJECT>
GpxCovariantDocumentItem<DOC_ITEM, GPX_OBJECT, HND_GPX_OBJECT>::
GpxCovariantDocumentItem(DOC_ITEM* item)
    : m_docItem(item)
{ }

template<typename DOC_ITEM, typename GPX_OBJECT, typename HND_GPX_OBJECT>
GpxCovariantDocumentItem<DOC_ITEM, GPX_OBJECT, HND_GPX_OBJECT>::
GpxCovariantDocumentItem(DOC_ITEM* item, const HND_GPX_OBJECT& hndGpx)
    : m_docItem(item),
      m_hndGpxObject(hndGpx)
{ }

template<typename DOC_ITEM, typename GPX_OBJECT, typename HND_GPX_OBJECT>
DOC_ITEM* GpxCovariantDocumentItem<DOC_ITEM, GPX_OBJECT, HND_GPX_OBJECT>::documentItem() const
{ return m_docItem; }

template<typename DOC_ITEM, typename GPX_OBJECT, typename HND_GPX_OBJECT>
Handle_AIS_InteractiveObject
GpxCovariantDocumentItem<DOC_ITEM, GPX_OBJECT, HND_GPX_OBJECT>::handleGpxObject() const
{ return m_hndGpxObject; }

template<typename DOC_ITEM, typename GPX_OBJECT, typename HND_GPX_OBJECT>
GPX_OBJECT* GpxCovariantDocumentItem<DOC_ITEM, GPX_OBJECT, HND_GPX_OBJECT>::gpxObject() const
{ return m_hndGpxObject.operator->(); }

} // namespace Mayo
