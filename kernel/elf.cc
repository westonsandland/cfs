#include "elf.h"
#include "machine.h"
#include "refs.h"
#include "bobfs.h"

uint32_t ELF::load(StrongPtr<Node> file) {
    ElfHeader hdr;

    file->readAll(0,&hdr,sizeof(ElfHeader));

    uint32_t hoff = hdr.phoff;

    for (uint32_t i=0; i<hdr.phnum; i++) {
        ProgramHeader phdr;
        file->readAll(hoff,&phdr,sizeof(ProgramHeader));
        hoff += hdr.phentsize;

#if 0
#else
        if (phdr.type == 1) {
            char *p = (char*) phdr.vaddr;
            uint32_t memsz = phdr.memsz;
            uint32_t filesz = phdr.filesz;

            Debug::printf("vaddr:%x memsz:0x%x filesz:0x%x fileoff:%x\n",
                p,memsz,filesz,phdr.offset);
            file->readAll(phdr.offset,p,filesz);
            bzero(p + filesz, memsz - filesz);
        }
#endif
    }

    return hdr.entry;
}
