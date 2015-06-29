NOTE: Please download the correct zip. This will replace the PerlCRT[D] that
is provided with ActivePerl builds 5xx. 

PerlCRT-2.05-bin-1-Alpha-VC.zip		non debug for the Alpha processor
PerlCRT-2.05-bin-1-debug-Alpha-VC.zip	debug for the Alpha processor

PerlCRT-2.05-bin-1-x86-VC.zip		non debug for the Intel processor
PerlCRT-2.05-bin-1-debug-x86-VC.zip	debug for the Intel processor

-----------------------------------------------------------------

PerlCRT.dll and PerlCRT.lib fix problems with MSVCRT.DLL

MSVCRT.DLL 6.0 has the following known bugs.
  1) On Win95 when a socket handle is passed to the open_osfhandle
     the call to GetFileType() returns FILE_TYPE_UNKNOWN rather
     than FILE_TYPE_CHAR.
  2) When using read() on a file that was opened in text mode,
     and the read terminates between a CR and LF the CR is not
     translated to a LF. FCRLF is used to pass this fact on to tell().

-----------------------------------------------------------------

Changes from 2.04
 o Added note about ActivePerl

Changes from 1.04
 o Built with 6.0 source.

Changes from 1.03
 o Corrected x64toa to convert negatives to positives before beginning
   conversions

Changes from 1.02
 o Corrected read to set FCRLF when reading more than requested size

Changes from 1.01
 o Fixed DST bug in time functions

Changes from 1.0
 o Added _free_oshndl to exports

-----------------------------------------------------------------

Building Perl to use with PerlCRT.dll and PerlCRT.lib currently
requires VC 5.0 with Service pack 3 or later
(Service pack 3 can be found at http://www.microsoft.com/vstudio/sp/)


Copy PerlCRT.dll to %SystemRoot%\system32 directory.
Copy PerlCRT.lib to a directory that is in the LIB environment variable.

If you are using nmake uncomment 'USE_PERLCRT	= define' in Makefile
If you are using dmake uncomment 'USE_PERLCRT	*= define' in makefile.mk

To build a version without DEBUGGING defined you will need the corresponding
non debug zip.

To build a version with DEBUGGING defined you will need the corresponding
debug zip.

----------------------------------------------------------------

Diffs for those who are interested:

diff -ru src.orig/OSFINFO.C src/OSFINFO.C
--- src.orig/OSFINFO.C	Tue Jun 16 23:59:59 1998
+++ src/OSFINFO.C	Wed Nov 03 11:46:19 1999
@@ -338,17 +338,12 @@
         /* find out what type of file (file/device/pipe) */
 
         isdev = GetFileType((HANDLE)osfhandle);
-        if (isdev == FILE_TYPE_UNKNOWN) {
-            /* OS error */
-            _dosmaperr( GetLastError() );   /* map error */
-            return -1;
-        }
 
         /* is isdev value to set flags */
-        if (isdev == FILE_TYPE_CHAR)
-            fileflags |= FDEV;
-        else if (isdev == FILE_TYPE_PIPE)
+        if (isdev == FILE_TYPE_PIPE)
             fileflags |= FPIPE;
+        else
+            fileflags |= FDEV;
 
 
         /* attempt to allocate a C Runtime file handle */
diff -ru src.orig/READ.C src/READ.C
--- src.orig/READ.C	Tue Jun 16 23:59:59 1998
+++ src/READ.C	Wed Nov 03 11:53:34 1999
@@ -175,10 +175,13 @@
             /* now must translate CR-LFs to LFs in the buffer */
 
             /* set CRLF flag to indicate LF at beginning of buffer */
-            if ( (os_read != 0) && (*(char *)buf == LF) )
-                _osfile(fh) |= FCRLF;
-            else
-                _osfile(fh) &= ~FCRLF;
+            /* set CRLF flag to indicate LF at beginning of buffer */
+            /* if ( (os_read != 0) && (*(char *)buf == LF) ) */
+            /*    _osfile(fh) |= FCRLF;                      */
+            /* else                                          */
+            /*    _osfile(fh) &= ~FCRLF;                     */
+
+            _osfile(fh) &= ~FCRLF;
 
             /* convert chars in the buffer: p is src, q is dest */
             p = q = buf;
@@ -221,12 +224,9 @@
                                have several possibilities:
                                1. disk file and char is not LF; just seek back
                                   and copy CR
-                               2. disk file and char is LF; seek back and
-                                  discard CR
-                               3. disk file, char is LF but this is a one-byte
-                                  read: store LF, don't seek back
-                               4. pipe/device and char is LF; store LF.
-                               5. pipe/device and char isn't LF, store CR and
+                               2. disk file and char is LF; store LF, don't seek back
+                               3. pipe/device and char is LF; store LF.
+                               4. pipe/device and char isn't LF, store CR and
                                   put char in pipe lookahead buffer. */
                             if (_osfile(fh) & (FDEV|FPIPE)) {
                                 /* non-seekable device */
@@ -239,10 +239,12 @@
                             }
                             else {
                                 /* disk file */
-                                if (q == buf && peekchr == LF) {
+                                if (peekchr == LF) {
                                     /* nothing read yet; must make some
                                        progress */
                                     *q++ = LF;
+                                    /* turn on this flag for tell routine */
+                                    _osfile(fh) |= FCRLF;
                                 }
                                 else {
                                     /* seek back */
End of Patch.

