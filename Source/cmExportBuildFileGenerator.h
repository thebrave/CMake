/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#ifndef cmExportBuildFileGenerator_h
#define cmExportBuildFileGenerator_h

#include "cmExportFileGenerator.h"
#include "cmListFileCache.h"

class cmExportSet;

/** \class cmExportBuildFileGenerator
 * \brief Generate a file exporting targets from a build tree.
 *
 * cmExportBuildFileGenerator generates a file exporting targets from
 * a build tree.  A single file exports information for all
 * configurations built.
 *
 * This is used to implement the EXPORT() command.
 */
class cmExportBuildFileGenerator : public cmExportFileGenerator
{
public:
  cmExportBuildFileGenerator();

  /** Set the list of targets to export.  */
  void SetTargets(std::vector<std::string> const& targets)
  {
    this->Targets = targets;
  }
  void GetTargets(std::vector<std::string>& targets) const;
  void AppendTargets(std::vector<std::string> const& targets)
  {
    this->Targets.insert(this->Targets.end(), targets.begin(), targets.end());
  }
  void SetExportSet(cmExportSet*);

  /** Set whether to append generated code to the output file.  */
  void SetAppendMode(bool append) { this->AppendMode = append; }

  void Compute(cmLocalGenerator* lg);

protected:
  // Implement virtual methods from the superclass.
  bool GenerateMainFile(std::ostream& os) CM_OVERRIDE;
  void GenerateImportTargetsConfig(
    std::ostream& os, const std::string& config, std::string const& suffix,
    std::vector<std::string>& missingTargets) CM_OVERRIDE;
  void HandleMissingTarget(std::string& link_libs,
                           std::vector<std::string>& missingTargets,
                           cmGeneratorTarget* depender,
                           cmGeneratorTarget* dependee) CM_OVERRIDE;

  void ComplainAboutMissingTarget(cmGeneratorTarget* depender,
                                  cmGeneratorTarget* dependee,
                                  int occurrences);

  /** Fill in properties indicating built file locations.  */
  void SetImportLocationProperty(const std::string& config,
                                 std::string const& suffix,
                                 cmGeneratorTarget* target,
                                 ImportPropertyMap& properties);

  std::string InstallNameDir(cmGeneratorTarget* target,
                             const std::string& config) CM_OVERRIDE;

  std::vector<std::string> FindNamespaces(cmGlobalGenerator* gg,
                                          const std::string& name);

  std::vector<std::string> Targets;
  cmExportSet* ExportSet;
  std::vector<cmGeneratorTarget*> Exports;
  cmLocalGenerator* LG;
};

#endif
