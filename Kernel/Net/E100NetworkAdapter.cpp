#include <Kernel/Net/E100NetworkAdapter.h>
#include <LibBareMetal/IO.h>

namespace Kernel {

void E100NetworkAdapter::detect() {
    static const PCI::ID qemu_id = { 0x8086, 0x1209 }; // Qemu i82550

    PCI::enumerate([&](const PCI::Address& address, PCI::ID id) {
        if (!address.is_null() && id == qemu_id) {
            u8 irq = PCI::get_interrupt_line(address);
            (void)adopt(*new E100NetworkAdapter(address, irq)).leak_ref();
        }
    });
}

E100NetworkAdapter::E100NetworkAdapter(PCI::Address address, u8 irq) 
    : PCI::Device(address, irq) {
        // interface name abreiviation for Intel Fast Ethernet
        set_interface_name("ife");
        klog() << "E100: Found @ " << pci_address();
}

E100NetworkAdapter::~E100NetworkAdapter() = default;

void E100NetworkAdapter::send_raw(const u8* data, size_t data_size) {
    (void) data;
    (void) data_size;
}

bool E100NetworkAdapter::link_up() {
    return true;
}

const char* E100NetworkAdapter::purpose() const {
    return class_name();
}

void E100NetworkAdapter::handle_irq(const RegisterState&) {

}
}