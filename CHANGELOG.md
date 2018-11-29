# Changelog
All notable changes to the lwpa library will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]
### Added
- This CHANGELOG file.
- lwpa_mempool: LWPA_MEMPOOL_DEFINE_ARRAY(), which allows a memory pool of
  fixed-size arrays of elements.

### Changed
- lwpa is now built with CMake. Documentation updated accordingly.
- Windows dependencies removed from unit tests - unit tests are now
  platform-neutral.

### Removed
- lwpa_uid (lwpa_uid.h and lwpa_uid.c) and estardm (estardm.h). These are now in
  the [RDM](https://github.com/ETCLabs/RDM) repository as rdm/uid.h, rdm_uid.c,
  and rdm/defs.h, respectively.
- estardmnet (estardmnet.h). This is now in the
  [RDMnet](https://github.com/ETCLabs/RDMnet) repository as rdmnet/defs.h.
- Visual Studio project files, as we now build with CMake.

## 0.1.0 - 2018-10-18
### Added
- Initial library modules, tests and documentation.

[Unreleased]: https://github.com/ETCLabs/lwpa/compare/master...develop