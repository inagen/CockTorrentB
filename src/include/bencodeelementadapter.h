//
// Created by Linux Oid on 24.04.2020.
//

#ifndef COCKTORRENT_BENCODEELEMENTADAPTER_H
#define COCKTORRENT_BENCODEELEMENTADAPTER_H

#include "bencode.h"
#include <exception>
#include <variant>

using BencodeCastError = std::bad_variant_access;

template<class ElementType>
class BencodeElementAdapter {
public:
    static_assert(std::is_same_v<bencode::BencodeElement, std::decay_t<ElementType>>,
                  "ElementType of BencodeElementAdapter must be BencodeElement");
    using IntegerType = bencode::BencodeInt;
    using StringType = bencode::BencodeString;
    using ArrayType = bencode::BencodeList;
    using DictType = bencode::BencodeDictionary;
    using SizeType  = bencode::BencodeList::size_type;

    explicit BencodeElementAdapter(ElementType *element);

    BencodeElementAdapter operator[](const std::string &s);

    BencodeElementAdapter operator[](const std::string &s) const;

    BencodeElementAdapter operator[](SizeType index);

    BencodeElementAdapter operator[](SizeType index) const;

    auto& integer();

    const auto & integer() const;

    auto &string();

    const auto &string() const;

    auto &array();

    const auto &array() const;

    auto &dictionary();

    const auto &dictionary() const;

    ElementType *element();

    ElementType *element() const;

private:
    ElementType *element_;
};

template<class ElementType>
BencodeElementAdapter<ElementType>::BencodeElementAdapter(ElementType *element) : element_(element) {}

template<class ElementType>
BencodeElementAdapter<ElementType>
BencodeElementAdapter<ElementType>::operator[](const std::string &s) {
    return BencodeElementAdapter(&std::get<DictType>(element_->data)[s]);
}

template<class ElementType>
BencodeElementAdapter<ElementType>
BencodeElementAdapter<ElementType>::operator[](const std::string &s) const {
    return BencodeElementAdapter(&std::get<DictType>(element_->data).at(s));
}

template<class ElementType>
BencodeElementAdapter<ElementType>
BencodeElementAdapter<ElementType>::operator[](BencodeElementAdapter::SizeType index) const {
    return BencodeElementAdapter(&std::get<ArrayType>(element_->data).at(index));
}

template<class ElementType>
BencodeElementAdapter<ElementType>
BencodeElementAdapter<ElementType>::operator[](BencodeElementAdapter::SizeType index) {
    return BencodeElementAdapter(&std::get<ArrayType>(element_->data).at(index));
}

template<class ElementType>
auto& BencodeElementAdapter<ElementType>::integer() {
    return std::get<BencodeElementAdapter<ElementType>::IntegerType>(element_->data);
}

template<class ElementType>
const auto& BencodeElementAdapter<ElementType>::integer() const {
    return std::get<BencodeElementAdapter<ElementType>::IntegerType>(element_->data);
}

template<class ElementType>
auto &BencodeElementAdapter<ElementType>::string() {
    return std::get<BencodeElementAdapter<ElementType>::StringType>(element_->data);
}

template<class ElementType>
const auto &BencodeElementAdapter<ElementType>::string() const {
    return std::get<BencodeElementAdapter<ElementType>::StringType>(element_->data);
}

template<class ElementType>
auto &BencodeElementAdapter<ElementType>::array() {
    return std::get<BencodeElementAdapter<ElementType>::ArrayType>(element_->data);
}

template<class ElementType>
auto &BencodeElementAdapter<ElementType>::dictionary() {
    return std::get<BencodeElementAdapter<ElementType>::DictType>(element_->data);
}

template<class ElementType>
const auto &BencodeElementAdapter<ElementType>::array() const {
    return std::get<BencodeElementAdapter<ElementType>::ArrayType>(element_->data);
}

template<class ElementType>
const auto &BencodeElementAdapter<ElementType>::dictionary() const {
    return std::get<BencodeElementAdapter<ElementType>::DictType>(element_->data);
}

template<class ElementType>
ElementType *BencodeElementAdapter<ElementType>::element() {
    return element_;
}

template<class ElementType>
ElementType *BencodeElementAdapter<ElementType>::element() const {
    return element_;
}


#endif //COCKTORRENT_BENCODEELEMENTADAPTER_H
