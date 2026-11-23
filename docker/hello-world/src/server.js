// Import the express module
const express = require('express');
const app = express();

// Define the port
const port = 3000;

// Define a default route
app.get('/', (req, res) => {
  res.send('Hello World!');
});

// Start the server
app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});
