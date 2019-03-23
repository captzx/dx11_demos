#pragma once

namespace insight {
	enum PipeResourceType {
		PRT_VERTEXBUFFER = 0x010000,
		PRT_INDEXBUFFER = 0x020000,
		PRT_CONSTANTBUFFER = 0x030000,
		PRT_STRUCTUREDBUFFER = 0x040000,
		PRT_BYTEADDRESSBUFFER = 0x050000,
		PRT_INDIRECTARGSBUFFER = 0x060000,
		PRT_TEXTURE1D = 0x070000,
		PRT_TEXTURE2D = 0x080000,
		PRT_TEXTURE3D = 0x090000
	};

	class PipeResource {
	public:
		PipeResource() {
			_uID = sIDCounter;
			++sIDCounter;
		}
		virtual ~PipeResource() {}

		virtual PipeResourceType GetType() = 0;
		virtual ID3D11Resource* GetResource() = 0;

		virtual unsigned int GetUID() { return _uID; }
		static unsigned int sIDCounter;
	protected:
		unsigned int _uID;
	};
}