const resolve = require("@rollup/plugin-node-resolve");
const commonjs = require("@rollup/plugin-commonjs");

const sharedPlugins = [
  resolve({
    jsnext: true,
    main: true,
    browser: true
  }),
  commonjs()
];

const watchConfig = {
  chokidar: {
    usePolling: true,
    interval: 100
  }
};

module.exports = [
    {
        input: "src/fractal/fractal.js",
        output: {
            dir: "dst/fractal",
            format: "iife",
            name: "Fractal",
            sourcemap: "inline"
        },
        plugins: sharedPlugins,
    },
    {
        input: "src/polyhedr/polyhedr.js",
        output: {
            dir: "dst/polyhedr",
            format: "iife",
            name: "Polyhedr",
            sourcemap: "inline"
        },
        plugins: sharedPlugins
    },
];