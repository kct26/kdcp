export default function ExtraLayout({ children }: { children: React.ReactNode }) {
  // Full-width workspace: the problem page manages its own two-panel layout.
  return <>{children}</>;
}
