import os
import shutil
import re

# Define the base directory for user homes
base_home_directory = "/home"
# Define the destination directory
destination_directory = "/home/public/RAT_Responses"
# Ensure the destination directory exists
if not os.path.exists(destination_directory):
    os.makedirs(destination_directory)

# Function to check if the directory name matches the expected format
def is_valid_user_dir(dirname):
    return re.match(r'^[a-zA-Z]+_\d+$', dirname) is not None

# Get a list of all user directories in /home
user_directories = [d for d in os.listdir(base_home_directory) 
                    if os.path.isdir(os.path.join(base_home_directory, d)) 
                    and is_valid_user_dir(d)]

for user_dir in user_directories:
    # Extract the lastname part (assuming the format is lastname_id)
    lastname = user_dir.split('_')[0]
    # Construct the expected file path
    expected_file_path = os.path.join(base_home_directory, user_dir, f"{lastname}.txt")

    # Check if the expected file exists
    if os.path.exists(expected_file_path):
        # Move the file to the destination directory
        try:
            shutil.move(expected_file_path, destination_directory)
            print(f"Moved: {expected_file_path}")
        except Exception as e:
            print(f"Error moving {expected_file_path}: {e}")

print("Operation completed.")

