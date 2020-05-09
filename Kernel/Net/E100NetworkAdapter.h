/*
 * Copyright (c) 2020, Tor Morten Finnesand <tmf@kvstech.no>
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

#include <AK/NonnullOwnPtrVector.h>
#include <AK/OwnPtr.h>
#include <Kernel/Interrupts/IRQHandler.h>
#include <Kernel/Net/NetworkAdapter.h>
#include <Kernel/PCI/Access.h>
#include <Kernel/PCI/Device.h>
#include <LibBareMetal/IO.h>

namespace Kernel {
    class E100NetworkAdapter final : public NetworkAdapter, public PCI::Device {
    public:
        E100NetworkAdapter(PCI::Address, u8 irq);
        virtual ~E100NetworkAdapter() override;
        static void detect();

        // Overrides from NetworkAdapter
        virtual void send_raw(const u8*, size_t) override;
        virtual bool link_up() override;
        virtual const char* purpose() const override;

    private:
        virtual void handle_irq(const RegisterState&) override;
        virtual const char* class_name() const override { return "E100NetworkAdapter"; }
    };
}
