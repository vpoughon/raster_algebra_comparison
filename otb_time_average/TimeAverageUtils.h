#include <vector>

namespace otb
{


template <typename PixelType>
class TimeAverageFunctor
{
public:
  using NArrayType = std::vector< PixelType >;

  PixelType operator()(const NArrayType& p)
  {
    PixelType result{};
    for(const auto& v : p)
      result += v;
    return result/p.size();;
  }

  bool operator!=(TimeAverageFunctor<PixelType> f)
  {
    return true;
  }
};

}
