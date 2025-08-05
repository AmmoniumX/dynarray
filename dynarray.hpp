#pragma once

#include <memory>
#include <stdexcept>
#include <algorithm>
#include <format>
#include <span>

template<typename T>
class DynArray {
    std::unique_ptr<T[]> data_;
    std::size_t size_;

public:
    DynArray() = delete;

    explicit DynArray(const std::size_t size) 
        : data_(std::make_unique<T[]>(size)), size_(size) {
    }

    DynArray(const T* const other, const std::size_t size) 
        : data_(std::make_unique<T[]>(size)), size_(size) {
        if (!other && size > 0) { throw std::runtime_error("Invalid pointer"); }
        std::copy(other, other + size, data_.get());
    }

    DynArray(std::initializer_list<T> init)
        : data_(std::make_unique<T[]>(init.size())), size_(init.size()) {
        std::copy(init.begin(), init.end(), data_.get());
    }

    DynArray(const DynArray& other)
        : data_(std::make_unique<T[]>(other.size_)), size_(other.size_) {
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    DynArray(const std::span<const T>& sp) 
        : data_(std::make_unique<T[]>(sp.size())), size_(sp.size()) {
        std::copy(sp.begin(), sp.end(), data_.get());
    }

    DynArray& operator=(const DynArray& other) {
        if (this == &other) return *this;
        // reuse array if possible to avoid extra allocations
        if (size_ != other.size_) {
            data_ = std::make_unique<T[]>(other.size_);
            size_ = other.size_;
        }
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
        return *this;
    }

    DynArray(DynArray&& other) noexcept
        : data_(std::move(other.data_)), size_(other.size_) {
        other.size_ = 0;
    }

    DynArray& operator=(DynArray&& other) noexcept {
        if (this == &other) return *this;
        data_ = std::move(other.data_);
        size_ = other.size_;
        other.size_ = 0;
        return *this;
    }

    ~DynArray() = default;

    // Element access methods: make operator[] unchecked and at() checked (like std::vector)
    T& operator[](std::size_t index) {
        return data_[index];
    }

    const T& operator[](std::size_t index) const {
        return data_[index];
    }

    
    T& at(std::size_t index) {
        if (index >= size_) throw std::out_of_range(std::format("Index out of bounds: {} not in [0, {}]", index, size_-1));
        return data_[index];
    }

    const T& at(std::size_t index) const {
        if (index >= size_) throw std::out_of_range(std::format("Index out of bounds: {} not in [0, {}]", index, size_-1));
        return data_[index];
    }

    std::size_t size() const { return size_; }

    T* data() { return data_.get(); }
    const T* data() const { return data_.get(); }

    T* begin() { return data_.get(); }
    T* end()   { return data_.get() + size_; }
    
    const T* begin() const { return data_.get(); }
    const T* end()   const { return data_.get() + size_; }
    
    const T* cbegin() const { return data_.get(); }
    const T* cend()   const { return data_.get() + size_; }

    std::span<T> span() { return { data_.get(), size_ }; }
    std::span<const T> span() const { return { data_.get(), size_ }; }
    std::span<const T> cspan() const { return { data_.get(), size_ }; }
};
