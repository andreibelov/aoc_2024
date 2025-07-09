# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    .gdbinit                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abelov <abelov@student.42london.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 23:27:33 by abelov            #+#    #+#              #
#    Updated: 2025/07/07 23:27:34 by abelov           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#layout reg
set disassemble-next-line on
set print static-members off
set print pretty on
set height unlimited
set pagination off
set confirm off
set max-value-size unlimited

directory ~/staging/glibc-2.31
directory ~/staging/glibc-2.31/elf
directory ~/staging/glibc-2.31/nptl
directory ~/staging/glibc-2.31/dlfcn
directory ~/staging/glibc-2.31/libio
directory ~/staging/glibc-2.31/misc
directory ~/staging/glibc-2.31/csu
directory ~/staging/glibc-2.31/ctype
directory ~/staging/glibc-2.31/stdlib
directory ~/staging/glibc-2.31/sysdeps
directory ~/staging/glibc-2.31/support
directory ~/staging/glibc-2.31/signal
directory ~/staging/glibc-2.31/string
directory ~/staging/glibc-2.31/stdio-common
directory ~/staging/gcc-9-9.4.0/src/libsanitizer/sanitizer_common
directory ~/staging/gcc-9-9.4.0/src/libsanitizer/asan
directory ~/staging/gcc-9-9.4.0/src/libsanitizer/ubsan
directory ~/staging/gcc-9-9.4.0/src/libsanitizer/ubsan
set trace-commands on
set print inferior-events on

br main
