#include "RTETrailStatic.h"
#include "../RTManager.h"


CTrailNewRoot& GetTrailNewRoot(void)
{
	static CTrailNewRoot _TrailNewRoot;

	return(_TrailNewRoot);
}


CTrailDeleteRoot& GetTrailDeleteRoot(void)
{
	static CTrailDeleteRoot _TrailDeleteRoot;

	return(_TrailDeleteRoot);
}


CTrailQuery& GetTrailQuery(void)
{
	static CTrailQuery _TrailQuery;

	return(_TrailQuery);
}


CRTETrailFunctor* GetRTETrailFunctor(const std::string _Name)
{
	static CRTManager<std::string, CRTETrailFunctor*> _RTETrailManager{
		{ "newroot",               &GetTrailNewRoot()                 },
		{ "deleteroot",            &GetTrailDeleteRoot()              },
		{ "query",                 &GetTrailQuery()                   },
	};

	return(_RTETrailManager[_Name]);
}

