/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkNetCDFPOPReader.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkNetCDFPOPReader - read NetCDF files
// .Author Joshua Wu 09.15.2009
// .SECTION Description
// vtkNetCDFPOPReader is a source object that reads NetCDF files.
// It should be able to read most any NetCDF file that wants to output a
// rectilinear grid.  The ordering of the variables is changed such that
// the NetCDF x, y, z directions correspond to the vtkRectilinearGrid
// z, y, x directions, respectively.  The striding is done with
// respect to the vtkRectilinearGrid ordering.  Additionally, the
// z coordinates of the vtkRectilinearGrid are negated so that the
// first slice/plane has the highest z-value and the last slice/plane
// has the lowest z-value.

#ifndef __vtkNetCDFPOPReader_h
#define __vtkNetCDFPOPReader_h

#include "vtkRectilinearGridAlgorithm.h"

class vtkDataArraySelection;
class vtkCallbackCommand;
class vtkNetCDFPOPReaderInternal;

class VTK_IO_EXPORT vtkNetCDFPOPReader : public vtkRectilinearGridAlgorithm
{
public:
  vtkTypeMacro(vtkNetCDFPOPReader,vtkRectilinearGridAlgorithm);
  static vtkNetCDFPOPReader *New();
  void PrintSelf(ostream& os, vtkIndent indent);

  //Description:
  //The file to open
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);

  //Description:
  //Enable subsampling in i,j and k dimensions in the vtkRectilinearGrid
  vtkSetVector3Macro(Stride, int);
  vtkGetVector3Macro(Stride, int);

  // Description:
  // Variable array selection.
  virtual int GetNumberOfVariableArrays();
  virtual const char *GetVariableArrayName(int idx);
  virtual int GetVariableArrayStatus(const char *name);
  virtual void SetVariableArrayStatus(const char *name, int status);

protected:
  vtkNetCDFPOPReader();
  ~vtkNetCDFPOPReader();

  int RequestData(vtkInformation*,vtkInformationVector**,
                  vtkInformationVector*);
  virtual int RequestInformation(vtkInformation* request,
                                 vtkInformationVector** inputVector,
                                 vtkInformationVector* outputVector);

  static void SelectionModifiedCallback(vtkObject *caller, unsigned long eid,
                                        void *clientdata, void *calldata);

  static void EventCallback(vtkObject* caller, unsigned long eid,
                            void* clientdata, void* calldata);

  vtkCallbackCommand* SelectionObserver;

  char *FileName;

  int NCDFFD; //netcdf file descriptor

  int Stride[3];

private:
  vtkNetCDFPOPReader(const vtkNetCDFPOPReader&);  // Not implemented.
  void operator=(const vtkNetCDFPOPReader&);  // Not implemented.

  vtkNetCDFPOPReaderInternal* Internals;
};
#endif
