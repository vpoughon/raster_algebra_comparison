#include "otbWrapperApplication.h"
#include "otbWrapperApplicationFactory.h"

#include "itkNaryAddImageFilter.h"

namespace otb
{

namespace Wrapper
{
class TimeAverage : public Application
{
public:
  typedef TimeAverage Self;
  typedef Application Superclass;
  typedef itk::SmartPointer<Self> Pointer;
  typedef itk::SmartPointer<const Self> ConstPointer;
  itkNewMacro(Self);
  itkTypeMacro(TimeAverage, otb::Application);

  // Image and pixel types
  typedef otb::VectorImage<int16_t, 2>       ImageType;
  typedef ImageType::InternalPixelType       ImagePixelType;

  // Filters and iterators
  typedef itk::NaryAddImageFilter<ImageType, ImageType> NaryAddImageFilterType;

private:
  void DoInit()
  {
    SetName("TimeAverage");
    SetDescription("");
    SetDocName("");
    SetDocLongDescription("");
    SetDocLimitations("None");
    SetDocAuthors("");
    SetDocSeeAlso("");
    AddDocTag(Tags::Analysis);
    AddDocTag("");

    AddParameter(ParameterType_InputImageList, "il", "Input images");
    AddParameter(ParameterType_OutputFilename, "out", "Output Image");

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
  }

};
} // namespace Wrapper
} //namespace otb

OTB_APPLICATION_EXPORT(otb::Wrapper::TimeAverage)

