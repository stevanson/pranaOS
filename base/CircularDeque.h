/*
 * Copyright (c) 2021, krishpranav
 *
 * SPDX-License-Identifier: BSD-2-Clause
*/

#pragma once

// includes
#include <base/CircularQueue.h>
#include <base/Types.h>

namespace Base {

template<typename T, size_t Capacity>
class CircularDeque : public CircularQueue<T, Capacity> {
public:
    template<typename U = T>
    void enqueue_begin(U&& value)
    {
        const auto new_head = (this->m_head - 1 + Capacity) % Capacity;
        auto& slot = this->elements()[new_head];
        if (this->m_size == Capacity)
            slot.~T();
        else
            ++this->m_size;

        new (&slot) T(forward<U>(value));
        this->m_head = new_head;
    }

    T dequeue_end()
    {
        VERIFY(!this->is_empty());
        auto& slot = this->elements()[(this->m_head + this->m_size - 1) % Capacity];
        T value = move(slot);
        slot.~T();
        this->m_size--;
        return value;
    }
};

}

using Base::CircularDeque;