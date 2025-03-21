import axios from 'axios';

const http = axios.create({
    baseURL: 'http://localhost:3002/proxy',
    timeout: 20000,
    headers: {
        "Content-Type": 'application/json',
    }

})

export default http;