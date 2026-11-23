# define the base image 
FROM node:latest 

# Copy src files to the working directory in the container
COPY package.json /app/
COPY src /app/ 

# define the working directory -> equivalent to cd in terminal
WORKDIR /app 

# define how the application runs
RUN npm install 

# define the command to run the application (normally the last line of the Dockerfile)
CMD ["node", "server.js"]
