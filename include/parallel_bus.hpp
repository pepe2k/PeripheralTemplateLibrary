/*
 * This file is part of the Peripheral Template Library project.
 *
 * Copyright (c) 2012-2013 Paul Sokolovsky <pfalcon@users.sourceforge.net>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <types.hpp>

template <typename type_width,
          class bit0 = None,
          class bit1 = None,
          class bit2 = None,
          class bit3 = None,
          class bit4 = None,
          class bit5 = None,
          class bit6 = None,
          class bit7 = None>
class ParBus;

// "Empty" partial specialization to stop recursion
template <typename type_width>
class ParBus<type_width,
             None, None, None, None,
             None, None, None, None>
{
public:
    static void write(type_width v) {}
    static type_width read() { return 0; }

    static void enable() {}
    static void input() {}
    static void output() {}
};

// Recursive template definition
template <typename type_width, class bit0, class bit1, class bit2, class bit3, class bit4, class bit5, class bit6, class bit7>
class ParBus : public ParBus<type_width, bit1, bit2, bit3, bit4, bit5, bit6, bit7, None>
{
    typedef ParBus<type_width, bit1, bit2, bit3, bit4, bit5, bit6, bit7, None> rest;
public:
    typedef type_width width;

    static void write(type_width v) {
        bit0::set(v & 0x01);
        rest::write(v >> 1);
    }

    static type_width read() {
        return (bool)bit0::value() | rest::read();
    }

    static void enable() {
        bit0::port::enable();
        rest::enable();
    }

    static void input() {
        bit0::input();
        rest::input();
    }

    static void output() {
        bit0::output();
        rest::output();
    }
};
