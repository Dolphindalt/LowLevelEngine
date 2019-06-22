#ifndef CSTRINGTABLE_H
#define CSTRINGTABLE_H

#include <cstring>
#include <set>

using std::pair;
using std::set;

class CStringTable;

class CFixedString
{
public:
    CFixedString();
    CFixedString(const CFixedString &);
    CFixedString &operator=(const CFixedString &);
    bool operator!=(const CFixedString &) const;
    bool operator==(const CFixedString &) const;
    bool operator<(const CFixedString &) const;
    operator bool() const { return mString && mString[0] != '\0'; }
    const char *getStr() const { return mString; }
private:
    friend class CStringTable;
    CFixedString(const char *);
    const char *mString;
};

class CStringTable
{
public:
    // the psuedo hash function
    CFixedString FixedString(const char *);
private:
    typedef set<const char *> StringSet;
    typedef pair<StringSet::iterator, bool> StringSetInsertResult;
    StringSet mTable;
};

inline CFixedString::CFixedString(const char *s)
: mString(s)
{}

inline CFixedString::CFixedString(const CFixedString &s)
: mString(s.mString)
{}

inline CFixedString::CFixedString()
: mString()
{}

inline CFixedString &CFixedString::operator=(const CFixedString &s)
{
    mString = s.mString;
    return *this;
}

inline bool CFixedString::operator!=(const CFixedString &o) const
{
    return mString != o.mString;
}

inline bool CFixedString::operator==(const CFixedString &o) const
{
    return mString == o.mString;
}

inline bool CFixedString::operator<(const CFixedString &o) const
{
    return mString < o.mString;
}

inline CFixedString CStringTable::FixedString(const char *s)
{
    StringSetInsertResult r = mTable.insert(s);
    return CFixedString(*r.first);
}

#endif