#!/usr/bin/expect

set timeout 10

expect_after {
    timeout {
        puts "----> timeout <----\r"
        exit
    }
}

spawn qemu-system-i386 -nographic -smp 4 --serial mon:stdio -hdc kernel/kernel.img

expect "| system shutdown\r"

send \001
send "x"
