# Free445-BOF
Code from https://github.com/DrJWCain/VFS/blob/master/Free445/Free445/Free445.cpp

## Compile

Please use [Actions](https://github.com/dust-life/Free445-BOF/actions)

## Usage
```
beacon> shell netstat -ano |findstr "445"
[*] Tasked beacon to run: netstat -ano |findstr "445"
[+] host called home, sent: 58 bytes
[+] received output:
  TCP    0.0.0.0:445            0.0.0.0:0              LISTENING       4
  TCP    [::]:445               [::]:0                 LISTENING       4

beacon> inline-execute C:\Users\Administrator\Desktop\Free445.o
[*] Tasked beacon to inline-execute C:\Users\Administrator\Desktop\Free445.o
[+] host called home, sent: 1312 bytes
[+] received output:
Found Transport: \Device\NetbiosSmb

[+] received output:
Deleted \Device\NetbiosSmb

[+] received output:
Found Transport: \Device\NetBT_Tcpip_{3291F33D-0E44-89D9-2912-333D62667590}

[+] received output:
Found Transport: \Device\NetBT_Tcpip_{2CJJ221A-8D33-291F-3921-D92392EI2199}

[+] received output:
Found Transport: \Device\NetBT_Tcpip_{29EEDDA1-49D1-4932-80DW-90BUI928291B}

[+] received output:
Total of 4 entries enumerated

beacon> shell netstat -ano |findstr "445"
[*] Tasked beacon to run: netstat -ano |findstr "445"
[+] host called home, sent: 58 bytes
```
