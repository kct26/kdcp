import type { Metadata } from "next";
import { Ubuntu, Geist_Mono } from "next/font/google";
import { Header } from "@/components/Header";
import { CopyCode } from "@/components/CopyCode";
import { themeScript } from "@/lib/theme";
import "./globals.css";

// Ubuntu is the UI font used by Kattis
const sans = Ubuntu({ subsets: ["latin"], weight: ["300", "400", "500", "700"], variable: "--font-ui" });
const mono = Geist_Mono({ subsets: ["latin"], variable: "--font-geist-mono" });

export const metadata: Metadata = {
  title: { default: "KDCP", template: "%s · KDCP" },
  description: "A 12-month competitive programming roadmap with notes, C++ code and practice problems.",
};

export default function RootLayout({ children }: { children: React.ReactNode }) {
  return (
    <html lang="en" className={`${sans.variable} ${mono.variable}`} suppressHydrationWarning>
      <head>
        <script dangerouslySetInnerHTML={{ __html: themeScript }} />
      </head>
      <body className="min-h-screen font-sans">
        <Header />
        {children}
        <CopyCode />
      </body>
    </html>
  );
}
