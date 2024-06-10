// script.js

// Function to add a donor
function addDonor() {
    // Get form values
    var name = document.getElementById('name').value;
    var bloodGroup = document.getElementById('bloodGroup').value;
    var units = document.getElementById('units').value;
    var contactDetails = document.getElementById('contactDetails').value;
    var email = document.getElementById('email').value;
    var date = document.getElementById('date').value;

    // Your AJAX logic to send data to the server
    // For simplicity, we'll assume a hypothetical API endpoint '/addDonor'
    // Replace this with your actual server endpoint
    fetch('/addDonor', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json',
        },
        body: JSON.stringify({
            name: name,
            bloodGroup: bloodGroup,
            units: units,
            contactDetails: contactDetails,
            email: email,
            date: date,
        }),
    })
    .then(response => response.json())
    .then(data => {
        // Display success message or handle errors
        console.log(data.message);
        // Optionally, update the table with the new donor data
        displayDonors();
    })
    .catch(error => {
        console.error('Error:', error);
    });
}

// Function to retrieve and display donors
function displayDonors() {
    // Your AJAX logic to get donor data from the server
    // For simplicity, we'll assume a hypothetical API endpoint '/getDonors'
    // Replace this with your actual server endpoint
    fetch('/getDonors')
    .then(response => response.json())
    .then(data => {
        // Update the table with donor data
        updateDonorsTable(data.donors);
    })
    .catch(error => {
        console.error('Error:', error);
    });
}

// Function to update the donors table
function updateDonorsTable(donors) {
    var tableBody = document.getElementById('donorsTable').getElementsByTagName('tbody')[0];

    // Clear existing rows
    tableBody.innerHTML = '';

    // Populate the table with donor data
    donors.forEach(donor => {
        var row = tableBody.insertRow();
        var cell1 = row.insertCell(0);
        var cell2 = row.insertCell(1);
        var cell3 = row.insertCell(2);
        var cell4 = row.insertCell(3);
        var cell5 = row.insertCell(4);
        var cell6 = row.insertCell(5);

        cell1.textContent = donor.name;
        cell2.textContent = donor.bloodGroup;
        cell3.textContent = donor.units;
        cell4.textContent = donor.contactDetails;
        cell5.textContent = donor.email;
        cell6.textContent = donor.date;
    });
}

// Initial display of donors
displayDonors();
