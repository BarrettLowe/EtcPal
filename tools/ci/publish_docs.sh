#!/bin/sh

# Adapted from the EXTREMELY helpful example script by Jeroen de Bruijn,
# available here: https://gist.github.com/vidavidorra/548ffbcdae99d752da02
#
# This script will generate Doxygen documentation and push the documentation to
# the gh-pages branch of a repository specified by GH_REPO_REF.
# Before this script is used there should already be a gh-pages branch in the
# repository.
# 
################################################################################

################################################################################
##### Setup this script and get the current gh-pages branch.               #####
echo 'Publishing documentation...'
# Exit with nonzero exit code if anything fails
set -e

if [ "$TRAVIS_PULL_REQUEST" != "false" || "$TRAVIS_BRANCH" != "develop" ]; then
  exit 0
fi

# Create a clean working directory for this script.
mkdir code_docs
cd code_docs

# Get the current gh-pages branch
git clone -b gh-pages https://git@$GH_REPO_REF
cd $GH_REPO_NAME

##### Configure git.
# Set the push default to simple i.e. push only the current branch.
git config --global push.default simple
# Pretend to be an user called Travis CI.
git config user.name "Travis CI"
git config user.email "travis@travis-ci.org"

# Remove everything currently in the relevant documentation directory on the
# gh-pages branch. GitHub is smart enough to know which files have changed and
# which files have stayed the same and will only update the changed files. So
# the directory can be safely cleaned, and it is sure that everything pushed
# later is the new documentation.
rm -rf docs/head/*

################################################################################
##### Generate the Doxygen code documentation and log the output.          #####
echo 'Generating Doxygen code documentation...'
# Redirect both stderr and stdout to the log file AND the console.
( cat $DOXYFILE ; echo "PROJECT_NUMBER=\"HEAD (unstable)\"" ; \
                  echo "OUTPUT_DIRECTORY=$(pwd)/docs/head" ; \
                  echo "HTML_OUTPUT=." ) \
                  | doxygen - 2>&1 | tee doxygen.log

# Debug
echo 'pwd'
pwd
echo 'ls docs'
ls docs
echo 'ls docs/head'
ls docs/head

################################################################################
##### Upload the documentation to the gh-pages branch of the repository.   #####
# Only upload if Doxygen successfully created the documentation.
# Check this by verifying that the html directory and the file html/index.html
# both exist. This is a good indication that Doxygen did it's work.
if [ -d "docs/head" ] && [ -f "docs/head/index.html" ]; then

    echo 'Uploading documentation to the gh-pages branch...'
    # Add everything in this directory (the Doxygen code documentation) to the
    # gh-pages branch.
    # GitHub is smart enough to know which files have changed and which files have
    # stayed the same and will only update the changed files.
    # git add --all

    # Commit the added files with a title and description containing the Travis CI
    # build number and the GitHub commit reference that issued this build.
    # git commit -m "Deploy code docs to GitHub Pages Travis build: ${TRAVIS_BUILD_NUMBER}" -m "Commit: ${TRAVIS_COMMIT}"

    # Force push to the remote gh-pages branch.
    # The ouput is redirected to /dev/null to hide any sensitive credential data
    # that might otherwise be exposed.
    # git push --force "https://${GH_REPO_TOKEN}@${GH_REPO_REF}" > /dev/null 2>&1
else
    echo '' >&2
    echo 'Warning: No documentation (html) files have been found!' >&2
    echo 'Warning: Not going to push the documentation to GitHub!' >&2
    exit 1
fi