/*
 * Copyright (c) 2018-2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/Noncopyable.h>
#include <AK/String.h>
#include <AK/Vector.h>
#include <LibVT/XtermColors.h>

namespace VT {

struct Attribute {
    Attribute() { reset(); }

    static const u32 default_foreground_color = xterm_colors[7];
    static const u32 default_background_color = xterm_colors[0];

    void reset()
    {
        foreground_color = default_foreground_color;
        background_color = default_background_color;
        flags = Flags::NoAttributes;
    }
    u32 foreground_color {};
    u32 background_color {};

    u32 effective_background_color() const { return flags & Negative ? foreground_color : background_color; }
    u32 effective_foreground_color() const { return flags & Negative ? background_color : foreground_color; }

    String href;
    String href_id;

    enum Flags : u8 {
        NoAttributes = 0x00,
        Bold = 0x01,
        Italic = 0x02,
        Underline = 0x04,
        Negative = 0x08,
        Blink = 0x10,
        Touched = 0x20,
    };

    bool is_untouched() const { return !(flags & Touched); }

    // TODO: it would be really nice if we had a helper for enums that
    // exposed bit ops for class enums...
    u8 flags = Flags::NoAttributes;

    bool operator==(const Attribute& other) const
    {
        return foreground_color == other.foreground_color && background_color == other.background_color && flags == other.flags;
    }
    bool operator!=(const Attribute& other) const
    {
        return !(*this == other);
    }
};

class Line {
    AK_MAKE_NONCOPYABLE(Line);
    AK_MAKE_NONMOVABLE(Line);

public:
    explicit Line(size_t length);
    ~Line();

    struct Cell {
        u32 code_point { ' ' };
        Attribute attribute;
    };

    const Attribute& attribute_at(size_t index) const { return m_cells[index].attribute; }
    Attribute& attribute_at(size_t index) { return m_cells[index].attribute; }

    Cell& cell_at(size_t index) { return m_cells[index]; }
    const Cell& cell_at(size_t index) const { return m_cells[index]; }

    void clear(const Attribute&);
    bool has_only_one_background_color() const;

    size_t length() const { return m_cells.size(); }
    void set_length(size_t);

    u32 code_point(size_t index) const
    {
        return m_cells[index].code_point;
    }

    void set_code_point(size_t index, u32 code_point)
    {
        m_cells[index].code_point = code_point;
    }

    bool is_dirty() const { return m_dirty; }
    void set_dirty(bool b) { m_dirty = b; }

private:
    Vector<Cell> m_cells;
    bool m_dirty { false };
};

}
