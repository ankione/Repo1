Qt5Xml.dll          C:\Qt\Qt5.14.1\Tools\QtCreator\bin\
libgcc_s_seh-1.dll   C:\Qt\Qt5.14.1\Tools\mingw730_64\x86_64-w64-mingw32\lib\
libwinpthread-1.dll   C:\Qt\Qt5.14.1\Tools\mingw730_64\x86_64-w64-mingw32\lib\
download PUTTY		ssh-keygen
			press enter for defaults
			scp key to remote host
			try ssh / scp to confirm
Environment Variable:
Path			%SystemRoot%\system32;
			%SystemRoot%;
			%SystemRoot%\System32\Wbem;
			%SYSTEMROOT%\System32\WindowsPowerShell\v1.0\
			C:\Qt\Qt5.14.1\Tools\QtCreator\bin\
			C:\Qt\Qt5.14.1\Tools\mingw730_64\x86_64-w64-mingw32\lib\
			C:\Qt\Qt5.14.1\5.14.0\mingw73_64\bin\
			C:\Program Files\PuTTY\


LINUX_VERSION	:

.pro file 	: 	
DEFINES+= LINE_ONE LINUX_VER

WINDOWS VERSION	:

.pro file 	:	DEFINES+= LINE_ONE LINUX_VER

Makefile	:	LIBS = C:\Qt\Qt5.14.1\Tools\mingw730_64\x86_64-w64-mingw32\lib\libws2_32.a

				C:\Qt\Qt5.13.1\Tools\mingw730_64\x86_64-w64-mingw32\lib\libws2_32.a

checksum command :
CertUtil -hashfile .exe md5(/sha1 etc)
