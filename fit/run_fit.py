import subprocess

# import os

# Define the path to your C++ executable
cpp_executable = "./MakeFitRun3"
background_file = "../root_io/tuples/Data_Combined_tuples.root"
signal_file = "../root_io/tuples/signals_Combined_tuples.root"

# os.makedirs(output_directory, exist_ok=True)

# bdt_selections = [0.0, 0.065, 0.162, 1.0]
bdt_selections = [0.0, 1.0]
input_arguments = []

for i in range(len(bdt_selections) - 1):
    input_arguments.append(
        [
            "--BkgFile=" + background_file,
            "--SigFile=" + signal_file,
            "--BDTbottomCut=" + str(bdt_selections[i]),
            "--BDTupperCut=" + str(bdt_selections[i + 1]),
            # "--category=Cat" + str(i),
            "--category=Cat" + str(5),
        ]
    )
print(input_arguments)

# Loop over each set of input arguments and execute the C++ program
for args in input_arguments:
    # Run the C++ executable with the current arguments
    result = subprocess.run([cpp_executable] + args, capture_output=True, text=True)

    # Print the output and any error messages
    print("Output:", result.stdout)
    print("Errors:", result.stderr)
