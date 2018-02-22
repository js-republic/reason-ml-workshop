const path = require('path');

module.exports = {
  entry: './src/core.bs.js',
  output: {
    filename: 'bundle.js',
    path: path.resolve(__dirname, 'dist')
  }
};
