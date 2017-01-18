#ifndef PARSER_CLIENT_IMPL_H
#define PARSER_CLIENT_IMPL_H

#include <set>

#include "data/graph/Node.h"
#include "data/parser/ParserClient.h"
#include "data/IntermediateStorage.h"
#include "data/graph/token_component/TokenComponentAccess.h"

#include "data/DefinitionType.h"

class ParserClientImpl: public ParserClient
{
public:
	ParserClientImpl();
	virtual ~ParserClientImpl();

	void setStorage(std::shared_ptr<IntermediateStorage> storage);
	void resetStorage();

	virtual void startParsingFile();
	virtual void finishParsingFile();

	virtual Id recordSymbol(
		const NameHierarchy& symbolName, SymbolKind symbolType,
		AccessKind access, DefinitionType definitionType);

	virtual Id recordSymbol(
		const NameHierarchy& symbolName, SymbolKind symbolType,
		const ParseLocation& location,
		AccessKind access, DefinitionType definitionType);

	virtual Id recordSymbol(
		const NameHierarchy& symbolName, SymbolKind symbolType,
		const ParseLocation& location, const ParseLocation& scopeLocation,
		AccessKind access, DefinitionType definitionType);

	virtual void recordReference(
		ReferenceKind referenceKind, const NameHierarchy& referencedName, const NameHierarchy& contextName,
		const ParseLocation& location);

	virtual void onError(const ParseLocation& location, const std::string& message, bool fatal, bool indexed);
	virtual void onLocalSymbolParsed(const std::string& name, const ParseLocation& location);
	virtual void onFileParsed(const FileInfo& fileInfo);
	virtual void onCommentParsed(const ParseLocation& location);

private:
	Node::NodeType symbolKindToNodeType(SymbolKind symbolType) const;
	Edge::EdgeType referenceKindToEdgeType(ReferenceKind referenceKind) const;
	void addAccess(Id nodeId, AccessKind access);
	Id addNodeHierarchy(NameHierarchy nameHierarchy, Node::NodeType nodeType = Node::NODE_UNDEFINED);

	Id addNode(Node::NodeType nodeType, NameHierarchy nameHierarchy);
	void addFile(Id id, const FilePath& filePath, const std::string& modificationTime);
	void addSymbol(Id id, DefinitionType definitionType);
	Id addEdge(int type, Id sourceId, Id targetId);
	Id addLocalSymbol(const std::string& name);
	void addSourceLocation(Id elementId, const ParseLocation& location, int type);
	void addComponentAccess(Id nodeId , int type);
	void addCommentLocation(const ParseLocation& location);
	void addError(const std::string& message, bool fatal, bool indexed, const ParseLocation& location);

	std::shared_ptr<IntermediateStorage> m_storage;
};

#endif // PARSER_CLIENT_IMPL_H
