#include "arch_tap_keys.h"

const char *macro_sequences[] = {
    "iwctl",
    "station wlan0 scan",
    "station wlan0 get-networks",
    "station wlan0 connect Wireless926",
    "exit",
    "timedatectl set-ntp true",
    "fdisk -l",
    "cfdisk /dev/nvme01np5",
    "mkfs.ext4 /dev/nvme0n1p5",
    "mkswap /dev/nvme0n1p6",
    "swapon /dev/nvme0n1p6",
    "mount /dev/nvme0n1p5 /mnt",
    "mount /dev/nvme0n1p1 /mnt/boot",
    "pacstrap /mnt base base-devel linux linux-firmware neovim",
    "genfstab -U /mnt >> /mnt/etc/fstab",
    "arch-chroot /mnt",
    "ln -sf /usr/share/zoneinfo/UTC /etc/localtime",
    "hwclock --systohc",
    "nvim /etc/locale.gen",
    "locale-gen",
    "echo 'LANG=en_US.UTF-8' > /etc/locale.conf",
    "echo 'hostname' > /etc/hostname",
    "nvim /etc/hosts",
    "passwd",
    "useradd -m -G wheel -s /bin/bash ra",
    "passwd ra",
    "EDITOR=nvim visudo",
    "pacman -S networkmanager",
    "pacman -Syu",
    "systemctl enable NetworkManager",
    "pacman -S grub",
    "grub-install --target=i386-pc /dev/sda",
    "grub-mkconfig -o /boot/grub/grub.cfg",
    "exit",
    "umount -R /mnt",
    "reboot",
    "",
};

uint8_t macro_index = 0;
uint8_t NUM_MACRO_SEQUENCES = sizeof(macro_sequences) / sizeof(char *);
uint8_t last_macro_length = 0;
uint16_t last_keycode = KC_NO;

bool macro_iterator_forward(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        if (last_keycode == M_FWRD || last_keycode == M_BACK) {
            for (uint8_t i = 0; i < last_macro_length; i++) {
                tap_code(KC_BSPC);
            }
        }
        macro_index = (macro_index + 1) % NUM_MACRO_SEQUENCES;
        send_string(macro_sequences[macro_index]);
        last_macro_length = strlen(macro_sequences[macro_index]);
    }
    last_keycode = keycode;
    return false;
}

bool macro_iterator_backward(uint16_t keycode, keyrecord_t *record, void *data) {
    if (record->event.pressed) {
        if (last_keycode == M_FWRD || last_keycode == M_BACK) {
            for (uint8_t i = 0; i < last_macro_length; i++) {
                tap_code(KC_BSPC);
            }
        }
        macro_index = (macro_index - 1 + NUM_MACRO_SEQUENCES) % NUM_MACRO_SEQUENCES;
        send_string(macro_sequences[macro_index]);
        last_macro_length = strlen(macro_sequences[macro_index]);
    }
    last_keycode = keycode;
    return false;
}

bool track_key_press(uint16_t keycode, keyrecord_t *record) {
    last_keycode = keycode;
    return true;
}
