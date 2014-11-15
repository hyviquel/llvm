
#include "DWARFRelocMap.h"

#include "llvm/ADT/SmallVector.h"
#include "llvm/DebugInfo/DWARFFormValue.h"

#include <cstdint>

namespace llvm {

class DWARFAcceleratorTable {

  struct Header {
    uint32_t Magic;
    uint16_t Version;
    uint16_t HashFunction;
    uint32_t NumBuckets;
    uint32_t NumHashes;
    uint32_t HeaderDataLength;
  };

  struct HeaderData {
    typedef uint16_t AtomType;
    uint32_t DIEOffsetBase;
    SmallVector<std::pair<AtomType, DWARFFormValue>, 1> Atoms;
  };

  struct Header Hdr;
  struct HeaderData HdrData;
  DataExtractor AccelSection;
  DataExtractor StringSection;
  const RelocAddrMap& Relocs;
public:
  DWARFAcceleratorTable(DataExtractor AccelSection, DataExtractor StringSection,
                        const RelocAddrMap &Relocs)
    : AccelSection(AccelSection), StringSection(StringSection), Relocs(Relocs) {}

  bool extract();
  void dump(raw_ostream &OS);
};

}
