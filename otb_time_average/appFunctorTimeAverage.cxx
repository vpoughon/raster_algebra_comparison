#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "otbMultiToMonoChannelExtractROI.h"
#include "itkNaryFunctorImageFilter.h"


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

namespace Wrapper
{
class FunctorTimeAverage : public Application
{
public:
  typedef FunctorTimeAverage Self;
  typedef Application Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  itkNewMacro(Self);
  itkTypeMacro(FunctorTimeAverage, otb::Application);

  // Image and pixel types
  typedef otb::Image<float, 2>               ImageType;
  typedef ImageType::InternalPixelType       ImagePixelType;
  typedef FloatVectorImageType               VectorImageType;
  typedef VectorImageType::InternalPixelType VectorImagePixelType;

  // Filters and iterators
  typedef otb::TimeAverageFunctor<ImagePixelType>   FunctorType;
  typedef otb::MultiToMonoChannelExtractROI<VectorImagePixelType, ImagePixelType>  ExtractChannelType;
  typedef itk::NaryFunctorImageFilter<ImageType, ImageType, FunctorType> NaryFunctorImageFilterType;

  void DoInit()
  {
    SetName("FunctorTimeAverage");
    SetDescription("");
    SetDocName("");
    SetDocLongDescription("");
    SetDocLimitations("None");
    SetDocAuthors("");
    SetDocSeeAlso("");
    AddDocTag(Tags::Analysis);
    AddDocTag("");

    AddParameter(ParameterType_InputImageList, "il", "Input images");
    AddParameter(ParameterType_OutputImage, "out", "Output Image");

    // System parameters
    AddParameter(ParameterType_RAM, "ram", "Available RAM");
    SetDefaultParameterInt("ram", 256);
    MandatoryOff("ram");
  }

  void DoUpdateParameters()
  {
  }

  void DoExecute()
  {
    FloatVectorImageListType::Pointer inList = GetParameterImageList("il");

    extractChannelFilters.resize(inList->Size(), NULL);
    naryAdder = NaryFunctorImageFilterType::New();
    FunctorType func{};
    naryAdder->SetFunctor(func);

    // For each input image
    for (unsigned int i = 0; i < inList->Size(); i++)
      {
      // Extract first band
      extractChannelFilters[i] = ExtractChannelType::New();
      extractChannelFilters[i]->SetInput(inList->GetNthElement(i));
      extractChannelFilters[i]->SetChannel(1);

      // Add it
      naryAdder->SetInput(i, extractChannelFilters[i]->GetOutput());
      }

    // Write
    SetParameterOutputImage("out", naryAdder->GetOutput());
  }

  // Filters
  std::vector<ExtractChannelType::Pointer> extractChannelFilters;
  NaryFunctorImageFilterType::Pointer naryAdder;
};
} // namespace Wrapper
} //namespace otb

OTB_APPLICATION_EXPORT(otb::Wrapper::FunctorTimeAverage)

