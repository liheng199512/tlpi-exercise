#ifndef INTERFACE_H
#define INTERFACE_H

// 4
int TestCopy(int argc, char *argv[]);
int TestEditor(int argc, char *argv[]);
int TestTee(int argc, char *argv[]);
int TestCopyHoles(int argc, char *argv[]);

// 5
int TestAtomicAppend(int argc, char *argv[]);
void TestDup();
void TestDupShare();
void TestDupWR();
void TestReadVWriteV();

#endif
