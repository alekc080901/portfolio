#ifndef LAB3_FILEFUNCTIONS_H

int checkFileExists(char* path);

int checkFileEmpty(int fd);

int getFileSize(int fd);

int getStringSize(int groupSize);

int writeInfo(int fd, void* info, size_t size);

void writeMeta(int fd);

int readMeta(int fd);

int readInfo(int fd, void* info, size_t size);

void deleteFile(char* filename);

int deleteGroup(int fd, char* groupName);

int seekToGroup(int fd, char* groupName);

int changeName(int fd, char* groupName, char* newGroupName);

int changeStudentsNumber(int fd, char* groupName, int newStudentsNumber);

int changeFemalesNumber(int fd, char* groupName, int femalesNumber);

int getStudentsNumber(int fd, char* groupName);

void saveFile(int fdDest, int fdSource);


#define LAB3_FILEFUNCTIONS_H

#endif
