/* Copyright (c) 2011 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef _FCALLS_H_
#define _FCALLS_H_ 1

#include <eprintf.h>
#include <style.h>
#include <where.h>
#include <wrapper.h>

/* Define macros to make it easier to test file system related system calls.
 * The goal is to wrap each system call so that when an error occurs, it is
 * easy to find the case that fails.
 *
 * Yes, this is a shameless abuse of macros but it makes the tests easier
 * to read and write (once you get used to it).
 *
 * Conventions:
 *   1. A macro is defined for each system call with the same name as the
 *      system call.
 *   2. A wrapper function is defined that is the name of system
 *      call followed by a 'k' which stands for check.
 *   3. A macro, <sys_call>Err, allows specific error cases to be checked.
 */

#define chdir(p)            chdirk    (WHERE, 0, p)
#define fchdir(fd)          fchdirk   (WHERE, 0, fd)

#define chmod(p, m)         chmodk    (WHERE, 0, p, m)
#define fchmod(fd, m)       fchmodk   (WHERE, 0, fd, m)

#define chown(p, o, g)      chownk    (WHERE, 0, p, o, g)
#define fchown(fd, o, g)    fchownk   (WHERE, 0, fd, o, g)
#define lchown(p, o, g)     lchownk   (WHERE, 0, p, o, g)

#define close(fd)           closek    (WHERE, 0, fd)
#define creat(p, m)         creatk    (WHERE, 0, p, m)

#define dup(ofd)            dupk      (WHERE, 0, ofd)
#define dup2(ofd, nfd)      dup2k     (WHERE, 0, ofd, nfd)
#define dup3(ofd, nfd, f)   dup3k     (WHERE, 0, ofd, nfd, f)

#define fcntl(fd, c, a)     fcntlk    (WHERE, 0, fd, c, a)
#define flock(fd, op)       flockk    (WHERE, 0, fd, op)
#define fsync(fd)           fsynck    (WHERE, 0, fd)
#define fdatasync(fd)       fdatasynck(WHERE, 0, fd)
#define ioctl(fd, r, a)     ioctlk    (WHERE, 0, fd, r, a)
#define link(po, pn)        linkk     (WHERE, 0, po, pn)

#define lseek(fd, o, w)     lseekk    (WHERE, 0, fd, o, w, o)
#define mkdir(p, m)         mkdirk    (WHERE, 0, p, m)

#define mmap(a, n, p, f, fd, o) mmapk (WHERE, 0, a, n, p, f, fd, o)
#define munmap(a, n)        munmapk   (WHERE, 0, a, n)

#define open(p, f, m)       openk     (WHERE, 0, p, f, m)
#define openat(fd, p, f, m) openatk   (WHERE, 0, fd, p, f, m)
#define pread(fd, b, n, o)  preadk    (WHERE, 0, fd, b, n, n, o)
#define pwrite(fd, b, n, o) pwritek   (WHERE, 0, fd, b, n, n, o)

#define read(fd, b, n)      readk     (WHERE, 0, fd, b, n, n)
#define readlink(p, b, n)   readlinkk (WHERE, 0, p, b, n, n)
#define readlinkat(fd, p, b, n) readlinkatk(WHERE, 0, fd, p, b, n, n)

#define rmdir(p)            rmdirk    (WHERE, 0, p)

#define stat(p, b)          statk     (WHERE, 0, p, b)
#define fstat(fd, b)        fstatk    (WHERE, 0, fd, b)
#define lstat(p, b)         lstatk    (WHERE, 0, p, b)

#define statfs(p, b)        statfsk   (WHERE, 0, p, b)
#define fstatfs(fd, b)      fstatfsk  (WHERE, 0, fd, b)
#define statvfs(p, b)       statvfsk  (WHERE, 0, p, b)
#define fstatvfs(fd, b)     fstatvfsk (WHERE, 0, fd, b)

#define symlink(po, pn)     symlinkk  (WHERE, 0, po, pn)
#define sync()              synck     (WHERE)

#define truncate(p, o)      truncatek (WHERE, 0, p, o)
#define ftruncate(fd, o)    ftruncatek(WHERE, 0, fd, o)
#define unlink(p)           unlinkk   (WHERE, 0, p)
#define write(fd, b, n)     writek    (WHERE, 0, fd, b, n, n)

#define closedir(dir)       closedirk (WHERE, 0, dir)
#define opendir(p)          opendirk  (WHERE, FALSE, p)
#define readdir(d)          readdirk  (WHERE, d)
#define readdir_r(d, t, r)  readdir_rk(WHERE, 0, d, t, r)
#define rewinddir(d)        rewinddirk(WHERE, d)
#define seekdir(d, o)       seekdirk  (WHERE, d, o)
#define telldir(d)          telldirk  (WHERE, 0, d)

#define chdirErr(e, p)            chdirk (WHERE, e, p)
#define closeErr(e, fd)           closek (WHERE, e, fd)
#define dupErr(e, ofd)            dupk   (WHERE, e, ofd)
#define lseekErr(e, fd, o, w)     lseekk (WHERE, e, fd, o, w, o)
#define mkdirErr(e, p, m)         mkdirk (WHERE, e, p, m)
#define openErr(e, p, f, m)       openk  (WHERE, e, p, f, m)
#define openatErr(e, fd, p, f, m) openatk(WHERE, e, fd, p, f, m)
#define readErr(e, fd, b, n)      readk  (WHERE, e, fd, b, n, n)
#define ftruncateErr(e, fd, o)    ftruncatek(WHERE, e, fd, o)
#define writeErr(e, fd, b, n)     writek    (WHERE, e, fd, b, n, n)

#define lseekCheckOffset(fd, o, w, s) lseekk(WHERE, 0, fd, o, w, s)
#define readCheckSize(fd, b, n, sz)   readk (WHERE, 0, fd, b, n, sz)
#define writeCheckSize(fd, b, n, sz)  writek(WHERE, 0, fd, b, n, sz)

#endif  /* _FCALLS_H_ */
