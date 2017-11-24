#ifndef NITROGEN_HEAPNODE_H
#define NITROGEN_HEAPNODE_H

namespace Nitrogen {

	struct HeapNode {
		HeapNode* last;
		HeapNode* next;
		unsigned int begin;
		unsigned int end;
		
		unsigned int getSize() const { return end - begin; }
		unsigned int getAddr() const { return begin; }
		
		HeapNode(HeapNode* last, HeapNode* next, unsigned int begin, unsigned int end) {
			this->last = last;
			this->next = next;
			this->begin = begin;
			this->end = end;
		}
		
		~HeapNode() {
			if (last != nullptr && next != nullptr) {
				last->next = next;
				next->last = last;
			}
		}
	};

}

#endif // NITROGEN_HEAPNODE_H