#ifndef LOGICAL_NODE
#define LOGICAL_NODE

#include "Definition.h"

#include <string>

using namespace std;

namespace Model {

class LogicalNode {
public:
    static constexpr UuidType null = 0;
    
    virtual ~LogicalNode() noexcept;
    
    NodeEnum getType() const noexcept;
    string getText() const noexcept;
    UuidType getUuid() const noexcept;
    UuidType getPrevious() const noexcept;
    bool isEnd() const noexcept;
    
    void setText(string t) noexcept;
    void setUuid(UuidType id) noexcept;
    void setPrevious(UuidType id) noexcept;
protected:
    NodeEnum type;
    string text;
    UuidType uuid;
    UuidType previous;

    LogicalNode(NodeEnum n, string t = "") noexcept;
};

}

#endif