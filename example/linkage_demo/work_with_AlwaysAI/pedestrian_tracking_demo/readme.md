# AlwaysAI 

Application that starts working with VCAM Cameras.

## Note
VCAM containers are in this format: alwaysai/edgeiq:vcam-\<arch\>-\<version\>.

VCAM models in the model catalogue are denoted with `vcam` in their name.

## Setup
1. This app requires an alwaysAI account. Head to the [Sign up page](https://www.alwaysai.co/dashboard) to create an account. 

   Follow the step-by-step [instructions](https://www.alwaysai.co/docs/get_started/development_computer_setup.html) to install the alwaysAI tools on your development machine.

2. Create an empty project.

3. Run aai app configure after cloning this repository. The new project will appear in the list. 

## Usage
Run the following CLI commands at the top level of the repo: 

Select project and  target device and run:

```
aai app configure
```

To build the app and install it on the target device: 

```
aai app install
```

To launch the app: 

```
aai app start
```

