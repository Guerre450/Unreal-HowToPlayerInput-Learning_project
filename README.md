# Header files
Declare variables & function used throught the script here, must be placed after the <a>GENERATED_BODY()</a> Annotation

// variable
``` c++
    // Input variable
    FVector CurrentAxisPos;
    FVector CurrentVelocity;
    bool bGrowing;

```
// functions
``` c++
public:
	//Input Functions
	void Move_XAxis(float AxisValue);

	void Move_YAxis(float AxisValue);

	void StartGrowing();

	void StopGrowing();

```

## UPROPERTY()
UPROPERTY() annotation allows to add a variable or function in the Unreal editor

here's how to declare a variable that can be modified in the editor:
``` c++
	UPROPERTY(EditAnywhere)
	USceneComponent* OurVisibleComponent;
```
We used the EditAnywhere flag to allow changes in the inspector

There's various other flags which allow interaction with blueprints & ect...(stuff I don't know atm)



## Components? wtf is that?
A components is a (thing?: object +/or functionality(script)) which is attached as part of another object, for example our object player as a Collision Component to handle collision, a camera component for the third person and a health component to handle health. 



# Unreal Objects

## USceneComponent 
placeholder class used as a parent to most other component, can be used as rootcomponent, to offset or to polymorph to other component




# CPP file

## Functions
remember that most function needs to be declared in header file. if you select a c++ Unreal class, you should get some code declared by default
### Tick
tick is called every frame
#### DeltaTime
time since the last frame, used to make movements and other fixed to the frame rate (lower frame or higher framerates can cause things to go quicker or slower without it)


### SetupPlayerInputComponent
Called to bind functionality to input






# How to implement stuffs


##  bind  actions
 in the function SetupPlayerInputComponent

 ### Binding an input action
``` c++
	InputComponent->BindAction("Grow",IE_Released,this,&AMyPawn::StopGrowing);
```
- Properties : Name of input, KeyEvent, pawn object, function to bind
 ### Binding an axis input
``` c++
	InputComponent->BindAxis("MoveX",this,&AMyPawn::Move_XAxis)
```
- Properties : Name of input, KeyEvent, pawn object, function to bind


### diferent function implementation

an input action will not need a parameter in it's function declaration since its tied to an event liker PRESSED or RELEASED

``` c++
void StartGrowing();
```
However, an axis input will need a float for a parameter which can go from -1.0f to 1.0f

``` c++
void Move_XAxis(float AxisValue);
```
Note: a clamp is recommended in the c++ tutorials to make sure that the input doesn't go outs our -1.0f to 1.0f range.




## Create a component
for example we can create a RootComponent to attach other component
``` c++
RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
```
### about RootComponent
the RootComponent variable is a variable declared by Unreal. It is intented that you assign a RootComponent to it which will be used to attach other component

## Attach a component
attach a component to another, in this exemple we will attach a camera to the root Component

``` c++
// Create Camera
OurCamera =  CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
// Attach Camera
OurCamera->SetupAttachment(RootComponent);
```
## Setting Relative location and rotation of a camera
We'll use the camera we created in the last section as an example again
### Location:


``` c++
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
```

### rotation
``` c++
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
```
the FRotator paramaters are InPitch, InYaw, InRoll.
They're all in degrees
	


## Component Scale

### getting component scale

``` c++
	OurVisibleComponent->GetComponentScale();
```
Returns a 3 float FVector
### setting component scale
``` c++
	OurVisibleComponent->SetWorldScale3D(FVector(2.0f,2.0f,2.0f));
```


## Moving Actor

### Getting the actor location

``` c++
GetActorLocation()
```
Returns a 3 float FVector : X,Y,Z
### updating the location depending on a input value
``` c++
CurrentSpeed = FMath::Clamp(CurrentSpeed, 0.0f, MaxSpeed);
CurrentVelocity = CurrentAxisPos * CurrentSpeed;
FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
```

### Setting the location

``` c++
SetActorLocation(NewLocation);
```






## Debugging messages:
Don't forget to check if GEngine is not null before exec GEgine function
``` c++
GEngine->AddOnScreenDebugMessage(-1,0.5f,FColor::Green, TEXT("bGrowing is true"));
```
the first parameter is the id, and the second is display time



# Variables that exists for some reasons

### AutoPossesPlayer
give the current pawn the player0 controls? heh?
``` c++
AutoPossessPlayer = EAutoReceiveInput::Player0;
```
	
## PrimaryActorTick
why is it off by default? seems like a odd implementation
``` c++
// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
```




# Helpers Classes which are nice to know

## FVector
Technically a vector which can be used for any dimension, 1d, 2d, 3d, ....
``` c++
FVector(1.0f,1.0f,1.0f, ...)
```
Note : has the function <a>IsZero()</a> which is used to determine if things are zero

## FMath
A helper namespace/class which includes a bunch of mathematical functions

here's a few exemples:
### Clamp
Used to keep values restricted to a certain bound.
``` c++
FMath::Clamp(AxisValue,-1.0f,1.0f);
```
Parameter : value, min, max