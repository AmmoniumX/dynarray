#pragma once

#include <algorithm>
#include <format>
#include <iterator>
#include <memory>
#include <span>
#include <stdexcept>

template <typename T> class DynArray {
  private:
    std::unique_ptr<T[]> data_;
    std::size_t size_;

  public:
    using value_type = T;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = T &;
    using const_reference = const T &;
    using pointer = T *;
    using const_pointer = const T *;
    using iterator = T *;
    using const_iterator = const T *;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    DynArray() = delete;

    explicit DynArray(const std::size_t size)
        : data_(std::make_unique<T[]>(size)), size_(size) {}

    DynArray(const T *const other, const std::size_t size)
        : data_(std::make_unique<T[]>(size)), size_(size) {
        if (!other && size > 0) {
            throw std::runtime_error("Invalid pointer");
        }
        std::copy(other, other + size, data_.get());
    }

    DynArray(std::initializer_list<T> init)
        : data_(std::make_unique<T[]>(init.size())), size_(init.size()) {
        std::copy(init.begin(), init.end(), data_.get());
    }

    DynArray(const DynArray &other)
        : data_(std::make_unique<T[]>(other.size_)), size_(other.size_) {
        std::copy(other.data_.get(), other.data_.get() + size_, data_.get());
    }

    DynArray(const std::span<const T> &sp)
        : data_(std::make_unique<T[]>(sp.size())), size_(sp.size()) {
        std::copy(sp.begin(), sp.end(), data_.get());
    }

    DynArray &operator=(const DynArray &other) {
        if (this == &other)
            return *this;
        DynArray temp(other);
        std::swap(*this, temp);
        return *this;
    }

    DynArray(DynArray &&other) noexcept
        : data_(std::move(other.data_)), size_(other.size_) {
        other.size_ = 0;
    }

    DynArray &operator=(DynArray &&other) noexcept {
        if (this == &other)
            return *this;
        data_ = std::move(other.data_);
        size_ = other.size_;
        other.size_ = 0;
        return *this;
    }

    ~DynArray() = default;

    // Element access methods: make operator[] unchecked and at() checked (like
    // std::vector)
    [[nodiscard]] T &operator[](std::size_t index) { return data_[index]; }

    [[nodiscard]] const T &operator[](std::size_t index) const {
        return data_[index];
    }

    [[nodiscard]] T &at(std::size_t index) {
        if (index >= size_)
            throw std::out_of_range(std::format(
                "Index out of bounds: {} not in [0, {}]", index, size_ - 1));
        return data_[index];
    }

    [[nodiscard]] const T &at(std::size_t index) const {
        if (index >= size_)
            throw std::out_of_range(std::format(
                "Index out of bounds: {} not in [0, {}]", index, size_ - 1));
        return data_[index];
    }

    [[nodiscard]] std::size_t size() const { return size_; }

    [[nodiscard]] T *data() { return data_.get(); }
    [[nodiscard]] const T *data() const { return data_.get(); }

    // Spans
    [[nodiscard]] std::span<T> span() { return {data_.get(), size_}; }
    [[nodiscard]] std::span<const T> span() const {
        return {data_.get(), size_};
    }
    [[nodiscard]] std::span<const T> cspan() const {
        return {data_.get(), size_};
    }

    // Forward iterators
    [[nodiscard]] iterator begin() noexcept { return data_.get(); }
    [[nodiscard]] iterator end() noexcept { return data_.get() + size_; }
    [[nodiscard]] const_iterator begin() const noexcept { return data_.get(); }
    [[nodiscard]] const_iterator end() const noexcept {
        return data_.get() + size_;
    }
    [[nodiscard]] const_iterator cbegin() const noexcept { return data_.get(); }
    [[nodiscard]] const_iterator cend() const noexcept {
        return data_.get() + size_;
    }

    // Reverse iterators
    [[nodiscard]] reverse_iterator rbegin() noexcept {
        return reverse_iterator(end());
    }
    [[nodiscard]] reverse_iterator rend() noexcept {
        return reverse_iterator(begin());
    }
    [[nodiscard]] const_reverse_iterator rbegin() const noexcept {
        return const_reverse_iterator(end());
    }
    [[nodiscard]] const_reverse_iterator rend() const noexcept {
        return const_reverse_iterator(begin());
    }
    [[nodiscard]] const_reverse_iterator crbegin() const noexcept {
        return const_reverse_iterator(cend());
    }
    [[nodiscard]] const_reverse_iterator crend() const noexcept {
        return const_reverse_iterator(cbegin());
    }
};
