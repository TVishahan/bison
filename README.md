# BISON: Batch Install Script Organization Nexus
## About
A simple, glorified script runner with the intention of running multiple bat scripts in multiple cmd prompt instances serially. The ideal use case is to run multiple silent installers for a Windows system to be SysPrepped. 

## Motivation
This program is designed and aimed at helping all three of you out there who are making installation scripts for a Windows image and want a way to organize and run those scripts. Certain install scripts will modify environment variables which require you to split your script into multiple sub scripts to be run one after the other, to facilitate this, BISON will let you spin up terminals consecutively so that you won't need to manually run those scripts one after the other.