
#ifndef FILESYSTEMMANAGER_FILEMANAGERLIBRARY_H
#define FILESYSTEMMANAGER_FILEMANAGERLIBRARY_H

#include <stdint.h>

typedef struct _partition{
    uint8_t bootable;
    uint8_t first_chs[3];
    uint8_t type;
    uint8_t last_chs[3];
    uint32_t lba_offset;
    uint32_t sector_count;} __attribute__((packed)) partition;


typedef struct BootSector {
    uint8_t jumpCode[3];
    uint8_t oemName[8];
    uint16_t bytesPerSector;
    uint8_t sectorsPerCluster;
    uint16_t reservedSectors;
    uint8_t numCopiesOfFAT;
    uint16_t maxRootDirEntries;
    uint16_t numSectorsSmall;
    uint8_t mediaDescriptor;
    uint16_t sectorsPerFAT;
    uint16_t sectorsPerTrack;
    uint16_t numHeads;
    uint32_t numHiddenSectors;
    uint32_t numSectorsLarge;
    uint16_t logicalDriveNumber;
    uint8_t extendedSignature;
    uint32_t serialNumber;
    uint8_t volumeName[11];
    uint8_t fatName[8];
    uint8_t executableCode[448];
    uint16_t executableMarker;
} __attribute__((packed)) BootSector;




typedef struct _MBR{
    uint8_t bootcode[446];
    partition part[4];
    uint16_t signature;} __attribute__((packed))MBR;


typedef struct FAT16Table {
    uint16_t entry[32768];   // each entry is 16 bits (2 bytes), and there are 16384 entries in a 32MB partition
} __attribute__((packed)) FAT16Table;



typedef struct RootDirectoryEntry {
    uint8_t filename[8];
    uint8_t ext[3];
    uint8_t attributes;
    uint16_t reserved1;
    uint16_t creationTime;
    uint16_t creationDate;
    uint16_t lastAccessDate;
    uint16_t reserved2;
    uint16_t modifiedTime;
    uint16_t modifiedDate;
    uint16_t startingCluster;
    uint32_t fileSize;
} __attribute__((packed)) RootDirectoryEntry;

typedef struct _BPB {
    uint16_t BPB_BytePerSec;
    uint8_t  BPB_SecPerClus;
    uint16_t BPB_RsvdSecCnt;
    uint8_t  BPB_NumFATs;
    uint16_t BPB_RootEntCnt;
    uint16_t BPB_TotSec16;
    uint8_t  BPB_Media;
    uint16_t BPB_FATSz16;
    uint16_t BPB_FATSz32;
    uint16_t BPB_SecPerTrk;
    uint16_t BPB_NumHeads;
    uint32_t BPB_HiddSec;
    uint32_t BPB_TotSec32;
} __attribute__((packed)) BPB;

void ListContents(const char* filename);

void ReadFileFromCluster(const char* filename, int cluster);


typedef struct RootDirectory{
    RootDirectoryEntry entries[512];
    int count;
} ROOTDIRECTORY;

typedef struct Directory {
    RootDirectoryEntry entry;
    struct Directory* parent;
    struct Directory* children;
    int childCount;
} Directory;

typedef struct FileSystem {
    Directory* root;
} FileSystem;


void addChild(Directory* parent, RootDirectoryEntry entry);

int ReadMBR(const char* filename);

void ListContents(const char* filename);

void readPartitions();
uint32_t reverse_uint32(uint32_t num);
int readLBA(uint32_t offset);
void printPartitions();
int readFatTables(uint32_t offset);
int readRootDir(uint32_t offset);
int readSubDir(uint32_t offset, uint16_t startingCluster, Directory* currentDir);
        void dumpRootDir();
int ParseUSB(const char* filename);
void dumpMBR();
void printRootDirCluster();
void printData();

#endif
