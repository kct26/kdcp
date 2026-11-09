import type { NextConfig } from "next";

// Set BASE_PATH (e.g. "/cp-roadmap") when hosting under a sub-path such as GitHub Pages.
const basePath = process.env.BASE_PATH || "";

const config: NextConfig = {
  output: "export",
  trailingSlash: true,
  basePath,
  images: { unoptimized: true },
};

export default config;
