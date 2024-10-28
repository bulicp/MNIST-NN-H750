# A step-by-Step Guide to Implementing a Neural Network for MNIST on STM32H750

This guide will walk you through the process of implementing, training, testing, and deploying a simple neural network for the MNIST dataset on the STM32H750 board. Here is a video of the working network: 
[MNIST NN on STM32H750](https://youtu.be/fTuEm3o_KBk)


## Prerequisites

- Python 3.x installed (or use Google Colab)
- PyTorch installed (or use Google Colab)
- ONNX installed (or use Google Colab)
- ST Edge AI Developer Cloud account
- STM32CubeIDE Integrated Development Environment for STM32
- STM32CubeProgrammer software for all STM32
- STM32H750B-DK Discovery kit with STM32H750XB MCU

## Link to PyTorch model on Google Colab: 
https://colab.research.google.com/drive/1iQkEjtpJQKhaohLlguWkb6Xao7NFnHPX?usp=sharing

## 1. Implementing the Neural Network in PyTorch

First, we create a simple feedforward neural network for recognizing handwritten digits from the MNIST dataset.

### 1.1 Import Required Libraries

```python
# Step 1: Import necessary libraries
import torch
import torch.nn as nn
import torch.optim as optim
import torchvision
import torchvision.transforms as transforms
import torch.nn.functional as F
import onnx
```

### 1.2 Define the Neural Network Architecture

```python
class SimpleNN(nn.Module):
    def __init__(self):
        super(SimpleNN, self).__init__()
        self.fc1 = nn.Linear(28 * 28, 128)   # Input layer to hidden layer
        self.fc2 = nn.Linear(128, 64)        # Hidden layer
        self.fc3 = nn.Linear(64, 10)         # Hidden layer to output layer

    def forward(self, x):
        x = x.view(-1, 28 * 28)  # Flatten the input tensor - reshape the input tensor into a flat vector of size 784. The -1 infers the batch size automatically.
        x = F.relu(self.fc1(x))  # Apply ReLU activation
        x = F.relu(self.fc2(x))  # Apply ReLU activation
        x = self.fc3(x)          # Output layer
        return x                 # return the final output from the output layer.
```




## 2. Training the Neural Network

### 2.1 Load the MNIST Dataset

```python
transform = transforms.Compose([  # A utility to chain together multiple image transformations
    transforms.ToTensor(), # Converts a PIL image or NumPy ndarray into a PyTorch tensor,
                           # scaling pixel values to the range [0, 1].
    transforms.Normalize((0.5,), (0.5,)) # Normalizes the tensor to have a mean of 0.5 and a standard deviation of 0.5
                                         # for each channel (MNIST images are single-channel).
])

train_dataset = torchvision.datasets.MNIST(root='./data', train=True, download=True, transform=transform)
test_dataset = torchvision.datasets.MNIST(root='./data', train=False, download=True, transform=transform)

# Set the batch size - defines the number of samples processed before the model is updated
# as MNIST train sat contains 60000 samples, we’ll have 60,000 / 64 = 937 mini-batches per epoch. The model updates its parameters 937 times per epoch.
# Mini-Batch Gradient Descent: When the batch_size is smaller than the full dataset,
# it's called mini-batch gradient descent. The training data is split into smaller batches,
# and the model's parameters are updated after processing each mini-batch.
# This is the most commonly used approach, as it strikes a balance between computation
# efficiency and convergence speed.

batch_size = 64

# shuffle=True randomizes the order of data for training to prevent learning order-dependent patterns.
train_loader = torch.utils.data.DataLoader(dataset=train_dataset, batch_size=batch_size, shuffle=True)
test_loader = torch.utils.data.DataLoader(dataset=test_dataset, batch_size=batch_size, shuffle=False)
```

### 2.2 Initialize the Network, Loss Function, and Optimizer

```python
net = SimpleNN()
criterion = nn.CrossEntropyLoss()
optimizer = optim.Adam(net.parameters(), lr=0.001)
```

### 2.3 Train the Network

```python
def train_model(model, train_loader, criterion, optimizer, num_epochs=5):
    for epoch in range(num_epochs):
        running_loss = 0.0
        for i, data in enumerate(train_loader):
            inputs, labels = data
            inputs, labels = inputs.to(device), labels.to(device)  # Move data to device

            optimizer.zero_grad()    # Zero the gradients
            outputs = model(inputs)  # Forward pass

            loss = criterion(outputs, labels)  # Compute loss
            loss.backward()    # Backward pass
            optimizer.step()   # Update weights

            running_loss += loss.item()  # Accumulate loss
            if i % 100 == 99:  # Print every 100 mini-batches
                print(f"Epoch {epoch + 1}, Batch {i + 1}, Loss: {running_loss / 100:.3f}")
                running_loss = 0.0  # Reset running loss
    print("Finished Training")

train_model(model, train_loader, criterion, optimizer, num_epochs=5)
```

## 3. Testing the Neural Network

To evaluate the performance of the trained model, we will test it on the MNIST test dataset.

### 3.1 Evaluate the Model

```python
def evaluate_model(model, test_loader):
    model.eval()  # Set the model to evaluation mode
    correct = 0
    total = 0
    with torch.no_grad():  # Disable gradient calculation
        for data in test_loader:
            images, labels = data
            images, labels = images.to(device), labels.to(device)  # Move data to device
            outputs = model(images)  # Forward pass
            _, predicted = torch.max(outputs.data, 1)  # Get the predicted class
            total += labels.size(0)  # Update total count
            correct += (predicted == labels).sum().item()  # Update correct count

    print(f'Accuracy on the test set: {100 * correct / total:.2f}%')

evaluate_model(model, test_loader)
```


## 4. Description of the Created Neural Network for MNIST

### Overview

The neural network implemented for the MNIST dataset is a simple feedforward network designed to classify handwritten digits (0-9). The network architecture consists of three fully connected layers.

### Architecture

- *Input Layer:* 
  - Size: 784 (28x28 pixels flattened into a vector)
  
- *Hidden Layer 1:*
  - Size: 128 neurons
  - Activation Function: ReLU (Rectified Linear Unit)

- *Hidden Layer 2:*
  - Size: 64 neurons
  - Activation Function: ReLU (Rectified Linear Unit)

- *Output Layer:*
  - Size: 10 neurons (one for each digit from 0 to 9)
  - Activation Function: Softmax (implicitly used in the CrossEntropyLoss)

### Functionality

1. **Forward Pass:**
   - The input image is flattened into a vector of size 784.
   - It passes through the first hidden layer, followed by a ReLU activation.
   - The output from the first layer is fed into the second hidden layer, again followed by a ReLU activation.
   - Finally, the output layer generates predictions for the digit classification.

2. **Training:**
   - The network is trained using the Cross Entropy Loss function to evaluate performance.
   - The Adam optimizer is used to minimize the loss during training.
   - Training is performed over multiple epochs with batches of data.

3. **Output:**
   - The network outputs the predicted class (digit) for each input image.
   - Accuracy is calculated based on the predictions compared to the true labels from the test dataset.

## 5. Exporting the Model to ONNX Format

After training and testing the model, we export it to the ONNX format.

### 5.1 Export the Model

```python
def export_model_to_onnx(model, file_name="mnist_model.onnx"):
    # Create a dummy input tensor with the same shape as your training data
    dummy_input = torch.randn(1, 1, 28, 28).to(device)  # Shape: [batch_size, channels, height, width]

    # Export the model
    torch.onnx.export(model, dummy_input, file_name,
                      export_params=True,
                      opset_version=11,
                      do_constant_folding=True,
                      input_names=['input'],
                      output_names=['output'])
    print(f"Model exported to {file_name}")

export_model_to_onnx(model)
```

## 6. Importing ONNX into ST Edge AI Developer Cloud and Creating the STM32 Project

### 6.1. Import ONNX

1. Log in to your ST Edge AI Developer Cloud account (https://stm32ai-cs.st.com/home).
2. Navigate to the **Your model library** section.
3. Click on **New Model** and select the `mnist_model.onnx` file.
4. Click **Start**.
5. The new page appeass (Select a platform). Select **STM32 MCUs**.

### 6.2. Quantizing the Model

1. After importing, select the model from your model list.
2. Click on **Quantization** to begin the process.
3. Choose the desired quantization parameters (e.g., INT8).
4. Click **Quantize** and wait for the process to complete.

### 6.3. Model benchmarking
1. Select the board and click **Start Benchmark**
2. Once the benchmark is finished, click on **...** and select **Generate code for this board**

### 6.4. Creating the Project for STM32H750

1. Now the **Generate your project** section appears.
2. On the bottom left locate **CPU/Series** and select **ARM Cortex-M7**
3. Select the **STM32H750-DK** board.
4. At the bottom of the page, click **Download** under **Download STM32CubeIDE Project**
5. a zip will be downloaded containing the STM32H750B-DK directory with sources.


---


## 7. Opening a Generated STM32CubeIDE Project in STM32CubeIDE

Once you've generated your project in the ST Edge AI Developer Cloud or from any other source, you can easily open it in STM32CubeIDE to begin development or testing. Follow the steps below:


1. **Launch STM32CubeIDE:**
   - Open STM32CubeIDE on your computer.

2. **Select the Workspace:**
   - Upon startup, STM32CubeIDE will prompt you to select a workspace.
   - Choose a workspace directory where you want to manage your STM32 projects, or select an existing workspace. I reccomend creating a new directory and using it as a workspace.

3. **Import the Project:**
   - copy the directory downloaded (named STM32H750B-DK) from ST Edge AI Developer Cloud and copy it into a newly created workspace directory.
   - Go to the **File** menu and select **Import0open Projects from File system**.
   - In the Import window, click **Directory** and locate and select STM32H750B-DK, then click **Next** or **Finish**

4. **Build the Project:**
   - Once the project is loaded, you can build it by right-clicking the project in the **Project Explorer** and selecting **Build Project**.

---

## 9. Programming and Debugging an STM32H750 Project with STM32CubeProgrammer and STM32CubeIDE

### 9.1. Flashing the Firmware using STM32CubeProgrammer with an External Loader

#### Step 1: Connect and Set Up the STM32H750 Board
- **Connect** your STM32H750 board to your computer via USB or another interface that supports flashing (e.g., ST-Link).
- **Power on** the board, ensuring it’s in a mode suitable for programming (e.g., BOOT0 pin configuration may need adjusting depending on the board).

#### Step 2: Open STM32CubeProgrammer
- Launch **STM32CubeProgrammer**.

#### Step 3: Connect to the Target
1. In STM32CubeProgrammer, **select the connection interface** (e.g., ST-Link).
2. Click **Connect**. STM32CubeProgrammer will attempt to detect and connect to the STM32H750 MCU.

#### Step 4: Select the External Loader
1. Go to **Options** > **External Loader**.
2. **Choose the appropriate external loader** for your board and memory type. For example, if your STM32H750 board has an external Flash memory (like QSPI or OctoSPI), select the loader specific to that memory type.
3. Apply the selection, which will allow STM32CubeProgrammer to recognize and use the external memory for flashing.

#### Step 5: Load and Flash the Firmware
1. In the **Download** section, click **Open file** and select the firmware file (typically a `.elf` file) generated by STM32CubeIDE.
2. Ensure the **Memory Type** (Internal or External) is set based on where you want the firmware loaded.
3. Click **Download** to program the firmware into the selected memory.

---

### 9.2. Configuring STM32CubeIDE to Debug Without Flashing

In some cases, you may want to start a debug session without re-flashing the firmware each time. Here’s how to configure STM32CubeIDE to allow this.

#### Step 1: Open Debug Configuration
1. In STM32CubeIDE, go to **** > **Debug Configurations…**.
2. In the **Debug Configurations** window, locate your project’s debug configuration under **STM32 MCU C/C++ Application**.

#### Step 2: Modify the Debug Settings to Skip Flashing
1. Select your project’s debug configuration and go to the **Starup** tab.
2. Select the elf file, click **Edit** and **Uncheck** the option labeled **Download** .This tells the debugger not to reflash the image during debugging.
3. Ensure that **Connect under reset** is checked, as it is often required to halt the MCU before it executes any application code.

#### Step 3: Apply the Configuration
- Click **Apply** to save your changes, and then click **Close**.

---

### 9.3. Starting the Debug Session Without Flashing

1. Once the configuration is saved, initiate the debug session by selecting the debug icon (the green bug icon) in STM32CubeIDE.
2. Use breakpoints, step-throughs, and other debug tools as usual to inspect the program’s execution.






## 10. **Generating a Quantized MNIST Test Subset for STM32 Testing**


Testing a neural network on an STM32H750 requires efficient, quantized data to match the 8-bit format of the deployed model. This script:
1. **Quantizes** MNIST images to 8-bit signed integers, ensuring they align with the STM32's model input.
2. **Creates a subset** of 100 random images and their labels from the MNIST test set.
3. **Generates a C header file** (`mnist_test_subset.h`) containing the quantized data, enabling direct use in embedded C code for STM32 testing.

### How the Script Works

#### Step 1: Import Libraries and Define Constants

The script imports essential libraries, defines the dataset size, and specifies input dimensions for the STM32 network.

```python
import numpy as np
import torch
from torchvision import datasets, transforms

# Constants
NUM_SAMPLES = 100
AI_NETWORK_IN_1_HEIGHT = 1
AI_NETWORK_IN_1_WIDTH = 28
AI_NETWORK_IN_1_CHANNEL = 28
AI_NETWORK_IN_1_SIZE = 784
AI_NETWORK_IN_1_SIZE_BYTES = 784
```

### Step 2: Load and Transform the MNIST Test Dataset
The script loads the MNIST test dataset and applies normalization to match the input requirements of the neural network model.
```python
transform = transforms.Compose([transforms.ToTensor(), transforms.Normalize((0,), (1,))])
mnist_test_dataset = datasets.MNIST(root='./data', train=False, download=True, transform=transform)
```

### Step 3: Select a Random Subset of Images
This step randomly selects 100 images from the MNIST test dataset, flattens each image from 28x28 to a 1D array, and stores them along with their labels.
```python
indices = np.random.choice(len(mnist_test_dataset), NUM_SAMPLES, replace=False)
images = []
labels = []

for idx in indices:
    img, label = mnist_test_dataset[idx]
    images.append(img.numpy().reshape(-1))  # Flatten the image to 1D
    labels.append(label)

```

### Step 4: Quantize the Images to Signed 8-bit Format
To fit the data into the model's 8-bit format, each image is converted to a range of -128 to 127.
```python
quantized_images = np.clip((np.array(images) * 255 - 128).astype(np.int8), -128, 127)
```


### Step 5: Generate the C Header File Content
The script creates a header file (mnist_test_subset.h) and writes the quantized images and labels in a C-compatible format, which makes it easy to import into an embedded application for testing. Finally, the script writes the generated header content to mnist_test_subset.h, making the test data ready for use in an STM32 project.

```python
# Generate header file content
header_file_content = f"""
#ifndef MNIST_TEST_SUBSET_H
#define MNIST_TEST_SUBSET_H

// Number of samples
#define MNIST_TEST_SUBSET_SIZE {NUM_SAMPLES}

// Input definitions
/*
#define AI_NETWORK_IN_1_HEIGHT      ({AI_NETWORK_IN_1_HEIGHT})
#define AI_NETWORK_IN_1_WIDTH       ({AI_NETWORK_IN_1_WIDTH})
#define AI_NETWORK_IN_1_CHANNEL     ({AI_NETWORK_IN_1_CHANNEL})
#define AI_NETWORK_IN_1_SIZE        ({AI_NETWORK_IN_1_SIZE})
#define AI_NETWORK_IN_1_SIZE_BYTES  ({AI_NETWORK_IN_1_SIZE_BYTES})
*/

// Test images data
const signed char mnist_test_subset_quantized[{NUM_SAMPLES}][{AI_NETWORK_IN_1_SIZE}] = {{
"""

# Append the quantized images to the header file content
for img in quantized_images:
    header_file_content += "    {" + ", ".join(map(str, img)) + "},\n"

header_file_content += "};\n\n"

# Labels for the corresponding images
header_file_content += f"const unsigned char mnist_test_subset_labels[{NUM_SAMPLES}] = {{ " + ", ".join(map(str, labels)) + " }};\n\n"

header_file_content += "#endif // MNIST_TEST_SUBSET_H\n"

# Write to header file
with open('mnist_test_subset.h', 'w') as f:
    f.write(header_file_content)

print("Header file 'mnist_test_subset.h' has been generated.")
```




## 11. Initializing and Running a Neural Network on STM32H750 with Cube.AI

Now, we’ll walk through setting up and running a neural network on the STM32H750 using STM32Cube.AI. Below are the necessary variables you’ll need to declare in `main.c` and explanations of each.

```c
/* USER CODE BEGIN PV */
const signed char (*mnist_test)[784] = mnist_test_subset_quantized;
const unsigned char* mnist_test_labels = mnist_test_subset_labels;

ai_handle network = AI_HANDLE_NULL;           // Handle to network instance
AI_ALIGNED(4) ai_u8 activations[AI_NETWORK_DATA_ACTIVATIONS_SIZE];  // Activation buffer
ai_network_report report;

// input/output data
AI_ALIGNED(4) ai_i8 network_output[AI_NETWORK_OUT_1_SIZE];
AI_ALIGNED(4) ai_i8 network_input[AI_NETWORK_IN_1_SIZE];
uint8_t recognized_digits[MNIST_TEST_SUBSET_SIZE] = {0}; 
/* USER CODE END PV */
```

- `mnist_test` : This is a pointer to the MNIST test data, structured as 784-element vectors. Each vector represents a single, quantized 28x28 grayscale image. 
- `mnist_test_subset_quantized` : This is an array of 100  MNIST test data. Theis array is declared in the `mnist_test_subset.h` file.
- `mnist_test_labels` : Pointer to the ground truth labels for each MNIST test image in the subset. Used to verify the network's predictions. The array of lables, `mnist_test_subset_labels`, is declared in the `mnist_test_subset.h` file.
- `network`: Handle for the network instance, initialized as AI_HANDLE_NULL. It is essential for managing the network instance in STM32Cube.AI.
- `activations`: This buffer is aligned to 4 bytes and used as the activation memory for the network. The size is specified by `AI_NETWORK_DATA_ACTIVATIONS_SIZE`. When implementing a neural network model using libraries like CMSIS-NN or other machine learning frameworks integrated within STM32CubeIDE, you need to allocate memory for the activation buffers and you should ensure that the bufer is allocated in like SRAM.
- `report`: A struct of type ai_network_report used to hold detailed network information after initialization (e.g., input/output dimensions, layer structure).
- `network_input` and `network_output`: Aligned 4-byte buffers for holding the network's input and output data, respectively. These will be populated with quantized MNIST data during inference.



### Function: `pa3_ai_network_init`

The `pa3_ai_network_init` function is responsible for creating and initializing the neural network instance for the STM32H750. It performs the following key tasks:

#### Function Definition

```c
ai_bool pa3_ai_network_init(void)
{
    // Create and initialize the network instance
    ai_error err = ai_network_create(&network, AI_NETWORK_DATA_CONFIG);
    if ((err.code != AI_ERROR_CODE_NONE) && (err.type != AI_ERROR_NONE)) {
        // Handle error: failed to create the network instance
        return false;
    }

    // Initialize the network with the activation memory buffer

    ai_network_params params = {
            AI_NETWORK_DATA_WEIGHTS(ai_network_data_weights_get()),     // Macro for getting weights
            AI_NETWORK_DATA_ACTIVATIONS(activations)               // Macro for setting activations buffer
    };

    if (!ai_network_init(network, &params)) {
        // Handle error: failed to initialize the network
        ai_error err = ai_network_get_error(network);
        return false;
    }
    return true;
}
```


The function begins by calling `ai_network_create` to create a network instance using the configuration defined in `AI_NETWORK_DATA_CONFIG`, which is in our case `NULL`.
Then, the function prepares the network parameters using the weights and activation memory buffer.
The `ai_network_params` structure is populated with:
- Weights: Retrieved via the macro `AI_NETWORK_DATA_WEIGHTS(ai_network_data_weights_get())`.
- Activations: Set using the macro `AI_NETWORK_DATA_ACTIVATIONS(activations)`.
The function `calls ai_network_init` with the network instance and the prepared parameters.

### Function: `pa3_ai_network_inference()`

The `pa3_ai_network_inference` function is designed to perform inference using a neural network on the STM32H750. It takes input data, processes it through the network, and outputs the results.

#### Function Definition

```c
ai_i32 pa3_ai_network_inference(ai_i8 *input_data, ai_i8 *output_data)
{
    // Configure the input and output buffers

	// NHWC (Batch, Height, Width, Channels): This is the most common format for images
	// Define input dimensions (batch, height, width, channels) ???
	//ai_shape_dimension input_shape_data[] = { 1, AI_NETWORK_IN_1_HEIGHT, AI_NETWORK_IN_1_WIDTH, AI_NETWORK_IN_1_CHANNEL };
	ai_shape_dimension input_shape_data[] = { 1, 28, 28, 1 };
	// Initialize the input buffer
	ai_buffer ai_input[AI_NETWORK_IN_NUM] = {
	{
		.format = AI_NETWORK_IN_1_FORMAT,  		// Set the format (AI_BUFFER_FORMAT_S8)
		.data = AI_HANDLE_PTR(input_data),  	// Pointer to the input data
		.meta_info = NULL,  					// No metadata info
		.flags = 0,  							// No specific flags
		.size = AI_NETWORK_IN_1_SIZE,  			// Number of elements in the buffer
		.shape = {  							// Input shape: [1, 1, 28, 28] based on the network input size
			.size = 4,  						// Number of dimensions
			.data = input_shape_data
		}
	}
	};

	// Define output dimensions (batch, number of classes)
	ai_shape_dimension output_shape_data[] = { 1, AI_NETWORK_OUT_1_SIZE, 1, 1};

	// Output buffer initialization
	ai_buffer ai_output[AI_NETWORK_OUT_NUM] = {
   {
		.format = AI_NETWORK_OUT_1_FORMAT,
		.data = AI_HANDLE_PTR(output_data),  	// Assuming output_data points to where the output will be stored
		.meta_info = NULL,
		.flags = 0,
		.size = AI_NETWORK_OUT_1_SIZE,       	// Total number of elements (10 in your case)
		.shape = {
			//.size = 2,
			.size = 4,
			.data = output_shape_data           // Batch size = 1, Number of classes = 10
		}
	}
	};

    // Run the network
    ai_i32 nbatch = ai_network_run(network, ai_input, ai_output);

    if (nbatch != 1) {
        // Handle error: inference failed
    	ai_error err = ai_network_get_error(network);
    	printf("Inference failed. Error type: %d, Error code: %d\n", err.type, err.code);
    	__NOP();
        return -1;
    }

    return 0;  // Inference successful
}
```

#### Parameters

- `ai_i8 *input_data`: Pointer to the input data that will be passed to the network. The data should be in the correct format and dimensions as required by the network.
- `ai_i8 *output_data`: Pointer to the buffer where the output data will be stored after inference. This buffercontains the network's predictions.

#### Function Overview

#### Configure Input Buffers:
The function defines the shape of the input data using the NHWC format (Batch, Height, Width, Channels), which is standard for image data. An array, `input_shape_data`, specifies the input dimensions: a batch size of 1, a height of 28, a width of 28, and 1 channel.

Here's a detailed explanation of the code snippet that initializes the input buffer for a neural network inference on the STM32H750:
```c
ai_shape_dimension input_shape_data[] = { 1, 28, 28, 1 };
ai_buffer ai_input[AI_NETWORK_IN_NUM] = {
	{
		.format = AI_NETWORK_IN_1_FORMAT,  		// Set the format (AI_BUFFER_FORMAT_S8)
		.data = AI_HANDLE_PTR(input_data),  	// Pointer to the input data
		.meta_info = NULL,  					// No metadata info
		.flags = 0,  							// No specific flags
		.size = AI_NETWORK_IN_1_SIZE,  			// Number of elements in the buffer
		.shape = {  							// Input shape: [1, 1, 28, 28] based on the network input size
			.size = 4,  						// Number of dimensions
			.data = input_shape_data
		}
	}
};
```
The code defines an array of `ai_buffer` structures named `ai_input`. The size of this array is determined by `AI_NETWORK_IN_NUM` (equals 1), which indicates how many input buffers are needed for the network.  Each element in the `ai_input` array is initialized with a series of fields that define the properties of the output buffer:
- `.format`: This specifies the format of the output data. The value `AI_NETWORK_IN_1_FORMAT` indicates the expected data type and layout for the input, an for this network it is actually thew type `AI_BUFFER_FORMAT_S8` for signed 8-bit integers.
- `.data`: This field points to the memory location where the output data will be stored. The macro `AI_HANDLE_PTR(input_data)` is used to cast `input_data` to the appropriate pointer type required by the AI framework. This allows the neural network to read its input directly from this buffer. It is assumed that `input_data` is allocated and ready to store the results of the inference.
- `.meta_info`: This is set to NULL, indicating that there is no additional metadata associated with this input buffer. Metadata might include information like data normalization parameters or other context-specific information.
- `.flags`:
This is initialized to 0, meaning that no special flags are set for this input buffer. Flags can be used to convey additional information about how the buffer should be handled or interpreted by the network.
- `.size`:
This field specifies the total number of elements in the input buffer. The value `AI_NETWORK_IN_1_SIZE` (equals 784) is used here, which should correspond to the expected size of the input data. In an image classification task, this typically matches the number of input pixels being processed.
- `.shape`:
The shape of the input buffer is defined using another structure that holds `size` and `data`:
  - `.size`: This indicates the number of dimensions in the input tensor. Here, it's set to 4, which reflects the NHWC format:
    - 1 for batch size (indicating that this inference is processing one image),
    - 28 for height,
    - 28 for width, and
    - 1 for channel 
  - `.data`: This is a pointer to `inputput_shape_data`, which holds the actual dimensions of the output. In this case, it defines the shape as an array representing the input configuration.




Here's a detailed explanation of the code snippet that initializes the output buffer for a neural network inference on the STM32H750:
```c
ai_shape_dimension output_shape_data[] = { 1, AI_NETWORK_OUT_1_SIZE, 1, 1};
ai_buffer ai_output[AI_NETWORK_OUT_NUM] = {
   {
       .format = AI_NETWORK_OUT_1_FORMAT,
       .data = AI_HANDLE_PTR(output_data),   // Assuming output_data points to where the output will be stored
       .meta_info = NULL,
       .flags = 0,
       .size = AI_NETWORK_OUT_1_SIZE,        // Total number of elements (10 in your case)
       .shape = {
           //.size = 2,
           .size = 4,
           .data = output_shape_data         // Batch size = 1, Number of classes = 10
       }
   }
};
```

The code defines an array of `ai_buffer` structures named `ai_output`. The size of this array is determined by `AI_NETWORK_OUT_NUM` (equals 1), which indicates how many output buffers are needed for the network. This could be more than one if the network has multiple outputs, but for this context, we are assuming a single output. Each element in the `ai_output` array is initialized with a series of fields that define the properties of the output buffer:
- `.format`: This specifies the format of the output data. The value `AI_NETWORK_OUT_1_FORMAT` indicates the expected data type and layout for the output, an for this network it is actually thew type `AI_BUFFER_FORMAT_S8` for signed 8-bit integers.
- `.data`: This field points to the memory location where the output data will be stored. The macro `AI_HANDLE_PTR(output_data)` is used to cast `output_data` to the appropriate pointer type required by the AI framework. This allows the neural network to write its output directly to this buffer. It is assumed that `output_data` is allocated and ready to store the results of the inference.
- `.meta_info`: This is set to NULL, indicating that there is no additional metadata associated with this output buffer. Metadata might include information like data normalization parameters or other context-specific information.
- `.flags`:
This is initialized to 0, meaning that no special flags are set for this output buffer. Flags can be used to convey additional information about how the buffer should be handled or interpreted by the network.
- `.size`:
This field specifies the total number of elements in the output buffer. The value `AI_NETWORK_OUT_1_SIZE` (equals 10) is used here, which should correspond to the expected size of the output data. In a classification task, this typically matches the number of classes being predicted (for example, 10 for digit classification).
- `.shape`:
The shape of the output buffer is defined using another structure that holds `size` and `data`:
  - `.size`: This indicates the number of dimensions in the output tensor. Here, it's set to 4, which reflects the NHWC format:
    - 1 for batch size (indicating that this inference is processing one image),
    - AI_NETWORK_OUT_1_SIZE (10) for height,
    - 1 for width, and
    - 1 for channels.
  - `.data`: This is a pointer to `output_shape_data`, which holds the actual dimensions of the output. In this case, it defines the shape as an array representing the output configuration.

 After the buffers initialization, we run the inference:
```c
ai_i32 nbatch = ai_network_run(network, ai_input, ai_output);
```
This function call runs the network using the initialized input and output buffers. It returns the number of batches processed. If `nbatch` is not equal to 1, it indicates an error in running the inference.



### main() function

In the `main()` function we create and initialize the network and run the inference over the whole input dataset. The following code presents only the part of the `main()` functin that contains the user code only (not the MX generated code):

```c
int main(void)
{
    // . . .

    /* USER CODE BEGIN 2 */
    // We should init some peripherals and external memories (QSPI FLASH and SDRAM):
    MX_USART3_UART_Init();
    BSP_QSPI_Init_t qspiInit;
    qspiInit.InterfaceMode=MT25TL01G_QPI_MODE;
    qspiInit.TransferRate= MT25TL01G_DTR_TRANSFER ;
    qspiInit.DualFlashMode= MT25TL01G_DUALFLASH_ENABLE;
    BSP_QSPI_Init(0,&qspiInit);
    BSP_QSPI_EnableMemoryMappedMode(0);
    BSP_SDRAM_Init(0);

    // Init network:
    if (!pa3_ai_network_init()) {
	    // Handle initialization error...
	    return -1;
	}

    // Loop over all MNIST_TEST_SUBSET_SIZE test samples;
    for (int i = 0; i < MNIST_TEST_SUBSET_SIZE; i++) {
	    // Copy the test sample data (uint8) into network input buffer (int8)
	    for (int j = 0; j < AI_NETWORK_IN_1_SIZE; j++) {
	        network_input[j] = (ai_i8)(mnist_test[i][j]);
	    }

	    // Run inference on the current sample
	    if (pa3_ai_network_inference(network_input, network_output) != 0) {
		    // Handle error... 
		    return -1;
	    }

	    int8_t max = -127;
	    int8_t digit = 0;
	    for(int k = 0; k < AI_NETWORK_OUT_1_SIZE ; k++) {
		    if (network_output[k] >= max){
			    max = network_output[k];
			    digit = k;
		    }
	    }
	    
        recognized_digits[i] = digit;
	}

    for(int i = 0; i < MNIST_TEST_SUBSET_SIZE; i++) {
	    if (recognized_digits[i] == mnist_test_labels[i]) {
		    success ++;
	    }
	}
	accuracy = (float)success / (float)MNIST_TEST_SUBSET_SIZE;

    // . . .


```


## Conclusion

I hope this guide will help you implement, train, test, and deploy a neural network for the MNIST dataset (or some other network) on the STM32H750 board. 


