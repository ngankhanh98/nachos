## Supported Function:
# Nachos
Not Another Completely Heuristic Operating System


## To-do tasks:
- [ ] 9. Viết chương trình echo, mỗi khi nhập một dòng từ console thì console xuất lại dòng đó
- [ ] 10. Viết chương trình cat , yêu cầu nhập vô filename, rồi hiển thị nội dung của file đó
- [ ] 11. Viết chương trình copy, yêu cầu nhập tên file nguồn và file đích và thực hiện copy


## Supported Function:

    int CreateFile(char *name);

**input:** filename (char*)<br>
**purpose:** create a new file<br>
**output:** 0 - succeed, -1 - if not<br>


    OpenFileId Open(char *name, int type)
**input:** filename (char*); <br>
type: 0 - readable & writeable, 1 - read-only<br>
**purpose:** open a file in fileSystem<br>
**output:** 0 - succeed, -1 - if not<br>

    int Read(char *buffer, int size, OpenFileId id);
**input:** filename (char*), size of string (int), file id (OpenFileId)<br>
**purpose:** read from file, store into char* buffer<br>
**output:** 0 - succeed, -1 - if not<br>

    int Write(char *buffer, int size, OpenFileId id);

**input:** string (char*), size of string (int), id of file (OpenFileId)<br>
**purpose:** copy string to file<br>
**output:** 0 - succeed, -1 - if not<br>

    int CloseFile(OpenFileId id);
**input:** file id (OpenFileId) ; <br>
**purpose:** close a file in fileSystem<br>
**output:** 0 - succeed, -1 - if not<br>

    int Seek(int pos, OpenFileId id);	
**input:** expecting position (int), file id;<br>
*pos=-1: length of file;*<br>
**purpose:** move _FILE pointer_ to place you wish<br>
**output:** 0 - succeed, -1 - if not<br>

    void Print(char *buffer);
like `printf("Hello world!");`<br>

    void Scan(char* buffer, int length);

like `scanf("%s", buffer);`<br>












