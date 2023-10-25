void __PRINT(int X)                  { cerr << X; };
void __PRINT(unsigned int X)         { cerr << X; };
void __PRINT(float X)                { cerr << X; };
void __PRINT(double X)               { cerr << X; };
void __PRINT(long X)                 { cerr << X; };
void __PRINT(unsigned long X)        { cerr << X; };
void __PRINT(long long X)            { cerr << X; };
void __PRINT(unsigned long long X)   { cerr << X; };
void __PRINT(long double X)          { cerr << X; };
void __PRINT(string X)               { cerr << '"' << X << '"'; };
void __PRINT(const char* X)          { __PRINT(string(X)); };
void __PRINT(char X)                 { cerr << '\'' << X << '\''; };
void __PRINT(bool X)                 { cerr << (X?'T':'F'); };
template <typename T1, typename T2>
void __PRINT(pair<T1, T2> X) {
  cerr << '(';
  __PRINT(X.first);
  cerr << ',';
  __PRINT(X.second);
  cerr << ')';
};
template <typename T>
void __PRINTWITHDELIM(T X, string DELIM=" ") {
  __PRINT(X);
  cerr<<DELIM;
}

template <typename TupleT, std::size_t... Is>
void printTupleImp(const TupleT& tp, std::index_sequence<Is...>) {
    size_t INDEX = max({Is...});
    cerr << "(";
    (__PRINTWITHDELIM(std::get<Is>(tp), (INDEX-->0 ? ",":"")), ...);
    cerr << ")";
}

template <typename TupleT, std::size_t TupSize = tuple_size<TupleT>::value>
void __PRINT(const TupleT &tp)
{
    printTupleImp(tp, std::make_index_sequence<TupSize>{});
}

template<typename _RandomAccessIterator>
void __PRINTCONTAINER(_RandomAccessIterator F, _RandomAccessIterator L, bool INDEX=false) {
  size_t index=0;
  for (auto it = F; it != L; it++) {
    if(INDEX) cerr<<index<<':';
    auto nxt = it; nxt++;
    if(nxt==L) __PRINT(*it);
    else __PRINTWITHDELIM(*it,",");
    index++;
  }
}

#define GET_MACRO(_1, _2, _3, NAME, ...) NAME
#define deb(...) GET_MACRO(__VA_ARGS__, DEB3, DEB2, DEB1)(__VA_ARGS__)
#define DEB1(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = "; __PRINT(_X); cerr << '\n';}
#define DEB2(F, L) { string _S = #F; cerr << "L" << __LINE__ << ": " << _S.substr(0, _S.find('.')) << " = ["; __PRINTCONTAINER(F,L); cerr << "]\n";}
#define DEB3(F, L, INDEX) { string _S = #F; cerr << "L" << __LINE__ << ": " << _S.substr(0, _S.find('.')) << " = [";__PRINTCONTAINER(F,L,INDEX);cerr << "]\n";}