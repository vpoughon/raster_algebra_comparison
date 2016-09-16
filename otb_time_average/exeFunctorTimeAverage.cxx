#include "otbImageFileReader.h"
#include "otbImageFileWriter.h"
#include "otbMultiToMonoChannelExtractROI.h"
#include "itkNaryFunctorImageFilter.h"
#include "TimeAverageUtils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{

  if(argc<3)
    {
    std::cout << "Usage : " << argv[0] << " image1 [image2 ... imageN] output\n";
    return 1;
    }
  // Image and pixel types
  typedef otb::Image<float, 2>               ImageType;
  typedef ImageType::InternalPixelType       ImagePixelType;
  typedef otb::VectorImage<float, 2>               VectorImageType;
  typedef VectorImageType::InternalPixelType VectorImagePixelType;

  // Filters and iterators
  typedef otb::TimeAverageFunctor<ImagePixelType>   FunctorType;
  typedef otb::MultiToMonoChannelExtractROI<VectorImagePixelType, ImagePixelType>  ExtractChannelType;
  typedef itk::NaryFunctorImageFilter<ImageType, ImageType, FunctorType> NaryFunctorImageFilterType;
  typedef otb::ImageFileReader<VectorImageType> ReaderType;
  typedef otb::ImageFileWriter<ImageType> WriterType;

  auto nb_images = argc-2;

  std::vector<ReaderType::Pointer> readers;  
  readers.reserve(nb_images);
  std::vector<ExtractChannelType::Pointer> extractChannelFilters;
  extractChannelFilters.reserve(nb_images);
  NaryFunctorImageFilterType::Pointer naryAdder;
  naryAdder = NaryFunctorImageFilterType::New();
  FunctorType func{};
  naryAdder->SetFunctor(func);

  // For each input image
  for (unsigned int i = 0; i < nb_images; i++)
    {
    readers[i] = ReaderType::New();
    readers[i]->SetFileName(argv[i+1]);
    // Extract first band
    extractChannelFilters[i] = ExtractChannelType::New();
    extractChannelFilters[i]->SetInput(readers[i]->GetOutput());
    extractChannelFilters[i]->SetChannel(1);

    // Add it
    naryAdder->SetInput(i, extractChannelFilters[i]->GetOutput());
    }

  // Write
  WriterType::Pointer writer = WriterType::New();
  writer->SetInput(naryAdder->GetOutput());
  writer->SetFileName(argv[argc-1]);
  writer->Update();
  return 0;
}



