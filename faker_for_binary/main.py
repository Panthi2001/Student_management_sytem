import os
from faker import Faker

class Student:
    """
    Represents a student with unique identifier, name, date of birth, and address.
    """
    def __init__(self, id, name, dob, address):
        """
        Initialize a Student object.

        Parameters:
            id (int): The unique identifier for the student.
            name (str): The name of the student.
            dob (str): The date of birth of the student in YYYY-MM-DD format.
            address (Address): The address object representing the student's address.
        """
        self.id = id
        self.name = name
        self.dob = dob
        self.address = address

class Address:
    """
    Represents an address with street, city, state abbreviation, and ZIP code.
    """
    def __init__(self, street, city, state, zip_code):
        """
        Initialize an Address object.

        Parameters:
            street (str): The street address.
            city (str): The city name.
            state (str): The abbreviation of the state.
            zip_code (str): The ZIP code.
        """
        self.street = street
        self.city = city
        self.state = state
        self.zip_code = zip_code

def generate_students(num_students):
    """
    Generate a list of student objects with unique IDs, names, dates of birth, and addresses.

    Parameters:
        num_students (int): The number of students to generate.

    Returns:
        list: A list of Student objects.
    """
    fake = Faker()
    students = []
    used_ids = set()  # To store used IDs
    for _ in range(num_students):
        id = fake.unique.random_number(digits=7)  # Generate a unique ID
        while id in used_ids:
            id = fake.unique.random_number(digits=7)
        used_ids.add(id)

        name = fake.name()
        dob = fake.date_of_birth(minimum_age=12)  # Minimum age of 12
        address = Address(fake.street_address(), fake.city(), fake.state_abbr(), fake.zipcode())
        student = Student(id, name, dob, address)
        students.append(student)
    return students

def write_to_txt(students, filename):
    """
    Write student data to a text file with comma-separated values.

    Parameters:
        students (list): A list of Student objects.
        filename (str): The name of the text file to write.
    """
    with open(filename, mode='w') as file:
        for student in students:
            # Remove comma from the full name
            full_name = student.name.replace(",", "")
            file.write(f"{student.id},{full_name},{student.dob},{student.address.street},{student.address.city},{student.address.state},{student.address.zip_code}\n")

def main():
    """
    Main function to generate student data and write it to a text file.
    """
    num_students = 100000
    filename = 'students.txt'
    current_directory = os.path.dirname(os.path.abspath(__file__))  # Get the directory where the script is located
    file_path = os.path.join(current_directory, filename)
    if os.path.exists(file_path):
        print("File already exists.")
        return

    students = generate_students(num_students)
    write_to_txt(students, file_path)
    print(f"Data written to {file_path}")

if __name__ == "__main__":
    main()
