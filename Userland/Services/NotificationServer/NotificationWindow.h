/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
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

#include <LibGUI/ImageWidget.h>
#include <LibGUI/Window.h>

namespace NotificationServer {

void update_notification_window_locations();

class NotificationWindow final : public GUI::Window {
    C_OBJECT(NotificationWindow);

public:
    virtual ~NotificationWindow() override;
    void set_original_rect(Gfx::IntRect original_rect) { m_original_rect = original_rect; };

    void set_text(const String&);
    void set_title(const String&);
    void set_image(const Gfx::ShareableBitmap&);

    static RefPtr<NotificationWindow> get_window_by_id(i32 id);

private:
    NotificationWindow(i32 client_id, const String& text, const String& title, const Gfx::ShareableBitmap&);

    Gfx::IntRect m_original_rect;
    i32 m_id;

    GUI::Label* m_text_label;
    GUI::Label* m_title_label;
    GUI::ImageWidget* m_image;
};

}
