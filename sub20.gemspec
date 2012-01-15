Gem::Specification.new do |s|
  s.name = 'sub20'
  s.version = '0.0.1'
  s.authors = ['Iuri Gagnidze']
  s.date = Time.now.utc.strftime('%Y-%m-%d')
  s.email = 'igagnidz@gmail.com'
  s.extensions = ['ext/sub20/extconf.rb']
  s.files = ['lib/sub20.rb']
  s.homepage = %q{http://github.com/igagnidz/sub20}
  s.rdoc_options = ['--charset=UTF-8']
  s.require_paths = ['lib']
  s.rubygems_version = %q{1.4.2}
  s.summary = %q{A simple, fast SUB-20 Multi Interface USB Adapter library for Ruby, binding to libsub}
end